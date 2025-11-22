#ifndef CIRCUITS_UI_H
#define CIRCUITS_UI_H

#include "Modifier.h"
#include "base/interface/IWidget.h"

namespace circuits {

    using WidgetList = std::initializer_list<WidgetPtr>;

    WidgetPtr label(const std::string& text, const Modifier& = {});
    WidgetPtr column(const WidgetList& list, const Modifier& = {});

}

#endif //CIRCUITS_UI_H