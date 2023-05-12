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

    torch::Tensor encodedPrompt = encode(prompt);

    auto nextLetter = model.forward({encodedPrompt.reshape({1, -1, 1})}).toTensor().argmax();
    while(nextLetter.item<int>() != 0){
       encodedPrompt = torch::cat({encodedPrompt, nextLetter.reshape({1})});
        nextLetter = model.forward({encodedPrompt.reshape({1, -1, 1})}).toTensor().argmax();
    }

    return decode(encodedPrompt);
}
