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
    friend int main();
    GenerativeModel();
    std::wstring generateNickname(const std::wstring &prompt = L"");
    std::vector<std::wstring> generateNames(const std::wstring &prompt, float alpha = 0.2, bool noise = true, int k = 10, int split_steps = 5);
};


#endif //DUMB_NICKNAME_GENERATOR_MODEL_H
