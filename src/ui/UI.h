#ifndef CIRCUITS_UI_H
#define CIRCUITS_UI_H

#include "layout/Column.h"

#include "widget/Button.h"
#include "widget/Label.h"

namespace circuits {

    using WidgetList = std::initializer_list<WidgetPtr>;

    std::shared_ptr<Column> column(const WidgetList& list, const Modifier& = {});

    std::shared_ptr<Label> label(const std::string& text, const Modifier& = {});
    std::shared_ptr<Button> button(const WidgetPtr& view, const ButtonCallback& callback = {},const Modifier& = {});

}

#endif //CIRCUITS_UI_H