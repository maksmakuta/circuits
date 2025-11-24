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
        const auto b = std::make_shared<Button>(label(text, Modifier().center().padding(8)));
        b->setModifier(mod);
        return b;
    }

    std::shared_ptr<Input> input(const std::string& text, const Modifier &mod) {
        const auto i = std::make_shared<Input>(text);
        i->setModifier(mod);
        return i;
    }

    std::shared_ptr<Toggle> toggle(bool state, const Modifier &mod) {
        const auto t = std::make_shared<Toggle>(state);
        t->setModifier(mod);
        return t;
    }

    std::shared_ptr<Image> image(Texture& tex, const Modifier &mod) {
        const auto t = std::make_shared<Image>(tex);
        t->setModifier(mod);
        return t;
    }

    std::shared_ptr<Card> card(const WidgetPtr& inner, const Modifier &mod) {
        const auto t = std::make_shared<Card>(inner);
        t->setModifier(mod);
        return t;
    }

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
