#include "UI.h"

#include "layout/Column.h"
#include "widget/Label.h"

namespace circuits {

    std::shared_ptr<Column> column(const WidgetList& list, const Modifier& m) {
        return std::make_shared<Column>(list,m);
    }

    std::shared_ptr<Label> label(const std::string& text, const Modifier& m) {
        return std::make_shared<Label>(text,m);
    }

    std::shared_ptr<Button> button(const WidgetPtr& view, const ButtonCallback& callback,const Modifier& m) {
        return std::make_shared<Button>(view,callback,m);
    }

}
