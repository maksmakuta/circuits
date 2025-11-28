#include "MainVM.h"

namespace circuits {

    MainVM::MainVM() {
        counter.observe([this](const int val) {
           counter_str = std::to_string(val);
        });
    }

    void MainVM::increment() {
        counter.setValue(counter.getValue() + 1);
    }

    void MainVM::decrement() {
        counter.setValue(counter.getValue() - 1);
    }

}
