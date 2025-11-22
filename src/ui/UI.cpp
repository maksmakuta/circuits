#include "UI.h"

#include "layout/Column.h"
#include "widget/Label.h"

namespace circuits {

    WidgetPtr label(const std::string& text, const Modifier& m) {
        return std::make_shared<Label>(text,m);
    }

    WidgetPtr column(const WidgetList& list, const Modifier& m) {
        return std::make_shared<Column>(list,m);
    }

}
