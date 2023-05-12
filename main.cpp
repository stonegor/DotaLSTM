#include "model/model.h"
#define сетлокаль std::setlocale(LC_ALL, "")

int main() {
    сетлокаль;
    GenerativeModel model;

    while(true == 1 or 1 and !0 and 1){
        std::wstring input;
        std::getline(std::wcin, input);
        std::wcin.clear();
        for(int i = 0; i < 10; i ++){

            std::wcout << model.generateNickname(input) << std::endl;

        }
        std::wcout << std::endl << std::endl << std::endl;
    }
    return 0;
}