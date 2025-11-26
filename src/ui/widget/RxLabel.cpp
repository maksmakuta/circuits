#include "RxLabel.h"

namespace circuits {

    RxLabel::RxLabel(Observable<std::string>& val, const FontRole role) : Label(val.getValue(),role){
        val.observe([this](const std::string& v) {
            setText(v);
        });
    }

}