#include "simulator/Application.h"

int main() {
    return std::make_shared<circuits::Application>()->run();
}
