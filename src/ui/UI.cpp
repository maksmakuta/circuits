#include "UI.h"

#include "theme/ThemeManager.h"
#include "widget/Label.h"

namespace circuits {

    std::shared_ptr<Label> label(const std::string& text, const Modifier& mod) {
        const auto l = std::make_shared<Label>(text);
        l->setModifier(mod);
        return l;
    }

    WidgetPtr button(WidgetPtr inner, Modifier mod);
    WidgetPtr button(std::string text, Modifier mod);
    WidgetPtr input(std::string text, Modifier mod);
    WidgetPtr toggle(bool state, Modifier mod);
    WidgetPtr image(Texture& tex, Modifier mod);
    WidgetPtr card(WidgetPtr inner, Modifier mod);
    WidgetPtr tooltip(WidgetPtr inner, Modifier mod);
    WidgetPtr notification(std::string message, Modifier mod);

    std::shared_ptr<Column> column(const WidgetList& list, const Modifier &mod) {
        const auto c = std::make_shared<Column>(list);
        c->setModifier(mod);
        return c;
    }

    WidgetPtr row(const WidgetList& list, Modifier mod);
    WidgetPtr grid(const WidgetList& list, Modifier mod);
    WidgetPtr box(const WidgetList& list, Modifier mod);


}
