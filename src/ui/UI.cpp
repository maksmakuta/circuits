#include "UI.h"

namespace circuits {

    template<typename T, typename... Args>
    std::shared_ptr<T> new_widget(const Modifier& m, Args&&... args) {
        auto w = std::make_shared<T>(std::forward<Args>(args)...);
        w->setModifier(m);
        return w;
    }

    std::shared_ptr<Label> label(const std::string& text, const FontRole& r,const Modifier& mod) {
       return new_widget<Label>(mod, text, r);
    }

    std::shared_ptr<Label> label(const std::string& text,const Modifier& mod) {
        return new_widget<Label>(mod, text, FontRole::Body);
    }

    std::shared_ptr<Button> button(const WidgetPtr& inner, const ButtonCallback& c, const Modifier &mod){
        return new_widget<Button>(mod, inner, c);
    }

    std::shared_ptr<Button> button(const std::string &text, const ButtonCallback& c, const Modifier &mod){
        return new_widget<Button>(mod, label(text, FontRole::Label, Modifier().center().padding(8)),c);
    }

    std::shared_ptr<Input> input(Observable<std::string>& text, const Modifier &mod) {
        return new_widget<Input>(mod, text);
    }

    std::shared_ptr<Toggle> toggle(Observable<bool>& state, const Modifier &mod) {
        return new_widget<Toggle>(mod, state);
    }

    std::shared_ptr<Image> image(const Texture& tex, const Modifier &mod) {
        return new_widget<Image>(mod, tex);
    }

    std::shared_ptr<Card> card(const WidgetPtr& inner, const Modifier &mod) {
        return new_widget<Card>(mod, inner);
    }

    std::shared_ptr<Card> card(const WidgetPtr& inner, const CardType type, const Modifier &mod) {
        return new_widget<Card>(mod, inner, type);
    }

    std::shared_ptr<Checkbox>  checkbox(bool val, const Modifier &mod) {
        return new_widget<Checkbox>(mod, val);
    }

    std::shared_ptr<Checkbox>  checkbox(Observable<bool>& val, const Modifier &mod) {
        return new_widget<Checkbox>(mod, val);
    }

    std::shared_ptr<Column> column(const WidgetList& list, const Modifier &mod) {
        return new_widget<Column>(mod, list);
    }

    std::shared_ptr<Row> row(const WidgetList& list, const Modifier &mod) {
        return new_widget<Row>(mod, list);
    }

    WidgetPtr grid(const WidgetList& list, Modifier mod);
    WidgetPtr box(const WidgetList& list, Modifier mod);

    std::shared_ptr<Label>  label(Observable<std::string>& text, const FontRole& r, const Modifier &mod) {
        return new_widget<Label>(mod, text, r);
    }

    std::shared_ptr<Label>  label(Observable<std::string>& text, const Modifier &mod) {
        return new_widget<Label>(mod, text, FontRole::Body);
    }

}
