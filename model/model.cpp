#include "model.h"

GenerativeModel::GenerativeModel() {
    model = torch::jit::load("path");

}
