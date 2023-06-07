#include "model/model.h"
#define сетлокаль std::setlocale(LC_ALL, "")

int main() {
    сетлокаль;
    GenerativeModel model;
    auto names = model.generateNames(L"");
    for(const auto& name : names){
        std::wcout << name << std::endl;
    }
    return 0;
}