#ifndef CIRCUITS_MAINVM_H
#define CIRCUITS_MAINVM_H

#include "core/IViewmodel.h"
#include "../../rx/Observable.h"

namespace circuits {

    class MainVM final : public IViewmodel{
    public:
        MainVM();


        Observable<int> counter{0};
    };

}

#endif //CIRCUITS_MAINVM_H