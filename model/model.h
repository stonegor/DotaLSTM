#ifndef DUMB_NICKNAME_GENERATOR_MODEL_H
#define DUMB_NICKNAME_GENERATOR_MODEL_H

#include <iostream>
#include <torch/torch.h>
#include <torch/script.h>
#include <memory>
#include <string>
#include <unordered_map>

class GenerativeModel{
    torch::jit::script::Module model;
    std::unordered_map<wchar_t, int> charToInt;
    std::wstring allowedChars = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя1234567890.-_()? ";
private:
    torch::Tensor encode(const std::wstring &prompt);
    std::wstring decode(const torch::Tensor &embedding);
public:
    GenerativeModel();
    std::wstring generateNickname(const std::wstring &prompt = L"");
    std::vector<std::wstring> generateNames(const std::wstring &prompt, float noiseAmount = 1, float alpha = 0.3, bool noise = true,  int k = 10, int split_steps = 6);
};


#endif //DUMB_NICKNAME_GENERATOR_MODEL_H
