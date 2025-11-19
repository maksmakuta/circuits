#ifndef CIRCUITS_MAINVM_H
#define CIRCUITS_MAINVM_H

#include "rx/State.h"

namespace circuits {

    class MainVM {
    public:
        MainVM() = default;

        void click() {
            const auto val = clicks.get();
            clicks.set(val + 1);
        }

        State<int> clicks{0};
    };

}

#endif //CIRCUITS_MAINVM_H