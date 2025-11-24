#ifndef CIRCUITS_UI_H
#define CIRCUITS_UI_H

#include "layout/Column.h"
#include "layout/Row.h"
#include "widget/Label.h"

namespace circuits {

    std::shared_ptr<Label> label(const std::string& text, const Modifier &mod = {});
    WidgetPtr button(WidgetPtr inner, Modifier mod = {});
    WidgetPtr button(std::string text, Modifier mod = {});
    WidgetPtr input(std::string text, Modifier mod = {});
    WidgetPtr toggle(bool state, Modifier mod = {});
    WidgetPtr image(Texture& tex, Modifier mod = {});

    WidgetPtr card(WidgetPtr inner, Modifier mod = {});
    WidgetPtr tooltip(WidgetPtr inner, Modifier mod = {});
    WidgetPtr notification(std::string message, Modifier mod = {});

    std::shared_ptr<Column> column(const WidgetList& list, const Modifier &mod = {});
    std::shared_ptr<Row> row(const WidgetList& list, const Modifier &mod = {});
    WidgetPtr grid(const WidgetList& list, Modifier mod = {});
    WidgetPtr box(const WidgetList& list, Modifier mod = {});

}

#endif //CIRCUITS_UI_H