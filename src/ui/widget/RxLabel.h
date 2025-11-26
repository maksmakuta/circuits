#ifndef CIRCUITS_RXLABEL_H
#define CIRCUITS_RXLABEL_H

#include "Label.h"
#include "rx/Observable.h"

namespace circuits {

    class RxLabel final : public Label{
    public:
        explicit RxLabel(Observable<std::string>&, FontRole role = FontRole::Body);
    };

}



#endif //CIRCUITS_RXLABEL_H