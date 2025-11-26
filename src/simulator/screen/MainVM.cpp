#include "MainVM.h"

#include "window/Event.h"

namespace circuits {

    MainVM::MainVM() {
        counter.observe([this](const int val) {
           counter_str.setValue(std::to_string(val));
            pushEvent(Event::Recompose());
        });
        counter.setValue(0);
    }

    void MainVM::increment() {
        counter.setValue(counter.getValue() + 1);
    }

    void MainVM::decrement() {
        counter.setValue(counter.getValue() - 1);
    }

}
