#ifndef CIRCUITS_UI_H
#define CIRCUITS_UI_H

#include "core/IWidget.h"

namespace circuits {

    using WidgetList = std::initializer_list<WidgetPtr>;

    WidgetPtr Label(std::string text, Modifier mod = {});
    WidgetPtr Button(WidgetPtr inner, Modifier mod = {});
    WidgetPtr Button(std::string text, Modifier mod = {});
    WidgetPtr Input(std::string text, Modifier mod = {});
    WidgetPtr Switch(bool state, Modifier mod = {});
    WidgetPtr Image(Texture& tex, Modifier mod = {});

    WidgetPtr Card(WidgetPtr inner, Modifier mod = {});
    WidgetPtr Tooltip(WidgetPtr inner, Modifier mod = {});
    WidgetPtr Notification(std::string message, Modifier mod = {});

    WidgetPtr column(const WidgetList& list, Modifier mod = {});
    WidgetPtr row(const WidgetList& list, Modifier mod = {});
    WidgetPtr grid(const WidgetList& list, Modifier mod = {});
    WidgetPtr box(const WidgetList& list, Modifier mod = {});

}

#endif //CIRCUITS_UI_H