#ifndef CIRCUITS_MAINVM_H
#define CIRCUITS_MAINVM_H

#include <string>

#include "core/IViewmodel.h"
#include "../../rx/Observable.h"

namespace circuits {

    class MainVM final : public IViewmodel{
    public:
        MainVM();

        void increment();
        void decrement();

        Observable<int> counter{0};
        Observable<std::string> counter_str{"0"};
    };

}

#endif //CIRCUITS_MAINVM_H