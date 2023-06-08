#include "model.h"

GenerativeModel::GenerativeModel() {
    model = torch::jit::load("model.pt");

    for(int i = 0; i < allowedChars.length(); i++){
        charToInt[allowedChars[i]] = i+2;
    }
}

torch::Tensor GenerativeModel::encode(const std::wstring &prompt) {
// vadikHYPE loh
    torch::Tensor encodedPrompt = torch::zeros({static_cast<long>(prompt.length()) + 1});
    encodedPrompt[0] = 1;
    for(int i = 0; i < prompt.length(); i++){
        encodedPrompt[i+1] = charToInt[prompt[i]];
    }
    return encodedPrompt;
}

std::wstring GenerativeModel::decode(const torch::Tensor &embedding) {
    std::wstring decodedOutput;
    decodedOutput.resize(embedding.size(0)-1);
    for(int i = 1; i < embedding.size(0); i++){
        int value = embedding[i].item<int>();
        if(value>1){
            decodedOutput[i-1] = allowedChars[value-2];
        }
    }
    return decodedOutput;
}

std::wstring GenerativeModel::generateNickname(const std::wstring &prompt) {
    // Encode the prompt
    torch::Tensor encodedPrompt = encode(prompt);

    // While model prediction != EOS token: make a new prediction
    auto nextLetter = model.forward({encodedPrompt.reshape({1, -1, 1})}).toTensor().argmax();
    while(nextLetter.item<int>() != 0){
       encodedPrompt = torch::cat({encodedPrompt, nextLetter.reshape({1})});
        nextLetter = model.forward({encodedPrompt.reshape({1, -1, 1})}).toTensor().argmax();
    }
    //return decoded predictions
    return decode(encodedPrompt);
}
std::vector<std::wstring> GenerativeModel::generateNames(const std::wstring &prompt,float noiseAmount, float alpha, bool noise,  int k, int split_steps){
    // Make encoded name our starting point
    std::vector<torch::Tensor> names = {encode(prompt)};
    torch::Tensor prediction0 = torch::ones(1);
    int steps = 0;
    // Generate name until prediction = EOS token
    while ((prediction0!=0).item<bool>()){
        auto predictions = model.forward({names[0].reshape({1, -1, 1})}).toTensor();
        auto topPredictions = torch::topk(predictions, k);

        prediction0 = std::get<1>(topPredictions)[0][0].reshape({1});
        auto value0 = std::get<0>(topPredictions)[0][0].reshape({1});
        auto noise_value = torch::zeros(1);
        // Splitting stage
        // At each iteration look at top k predictions.
        // If ratio of confidence of top prediction to i-th prediction is less than 1 - alpha + noise,
        // append new variant to names
        if (steps < split_steps){
            for (int i = 1; i < k; i++){
                auto valuei = std::get<0>(topPredictions)[0][i].reshape({1});
                auto predictioni = std::get<1>(topPredictions)[0][i].reshape({1});

                if (noise){
                    noise_value = torch::rand({1}) * noiseAmount;
                }

                if ((value0/valuei < 1 + alpha + noise_value).item<bool>()){
                    names.push_back(torch::cat({names[0], predictioni}, 0));
                }
            }
        }

        names[0] = torch::cat({names[0], prediction0}, 0);
        steps+=1;
    }
    // complete all added names at splitting stage
    for (int i = 1; i < names.size(); i++){
        torch::Tensor prediction = torch::ones(1);
        while ((prediction!=0).item<bool>()){
            prediction = model.forward({names[i].reshape({1, -1, 1})}).toTensor().argmax().reshape({1});
            names[i] = torch::cat({names[i], prediction}, 0);
        }
    }
    // Decode all names
    std::vector<std::wstring> decoded_names;
    for (const auto& name : names){
        decoded_names.push_back(decode(name));
    }
    return decoded_names;
}
