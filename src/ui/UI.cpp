#include "UI.h"

namespace circuits {

    std::shared_ptr<Label> label(const std::string& text, const Modifier& mod) {
        const auto l = std::make_shared<Label>(text);
        l->setModifier(mod);
        return l;
    }

    std::shared_ptr<Button> button(const WidgetPtr& inner, const Modifier &mod){
        const auto b = std::make_shared<Button>(inner);
        b->setModifier(mod);
        return b;
    }

    std::shared_ptr<Button> button(const std::string &text, const Modifier &mod){
        const auto b = std::make_shared<Button>(label(text));
        b->setModifier(mod);
        return b;
    }

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

    std::shared_ptr<Row> row(const WidgetList& list, const Modifier &mod) {
        const auto r = std::make_shared<Row>(list);
        r->setModifier(mod);
        return r;
    }

    WidgetPtr grid(const WidgetList& list, Modifier mod);
    WidgetPtr box(const WidgetList& list, Modifier mod);


}
