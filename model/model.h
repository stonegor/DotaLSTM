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
    std::unordered_map<char, int> charToInt;
    std::string allowedChars = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя1234567890.-_()?";
private:
    torch::Tensor encode(std::string prompt);
    std::string decode(torch::Tensor);
public:
    GenerativeModel();
    std::string generateNickname(std::string prompt = "");


};


#endif //DUMB_NICKNAME_GENERATOR_MODEL_H
