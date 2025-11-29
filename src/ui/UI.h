#ifndef CIRCUITS_UI_H
#define CIRCUITS_UI_H

#include "layout/Box.h"
#include "layout/Column.h"
#include "layout/Row.h"

#include "widget/Button.h"
#include "widget/Card.h"
#include "widget/Checkbox.h"
#include "widget/Image.h"
#include "widget/Input.h"
#include "widget/Label.h"
#include "widget/RadioButton.h"
#include "widget/RadioGroup.h"
#include "widget/Toggle.h"

namespace circuits {

    std::shared_ptr<Label>  label(const std::string& text, const FontRole& r = FontRole::Body, const Modifier &mod = {});
    std::shared_ptr<Label>  label(Observable<std::string>& text, const FontRole& r = FontRole::Body, const Modifier &mod = {});
    std::shared_ptr<Label>  label(const std::string& text, const Modifier &mod = {});
    std::shared_ptr<Label>  label(Observable<std::string>& text, const Modifier &mod = {});

    std::shared_ptr<Button> button(const WidgetPtr& inner, const ButtonCallback& = {}, const Modifier &mod = {});
    std::shared_ptr<Button> button(const std::string &text, const ButtonCallback& = {}, const Modifier &mod = {});

    std::shared_ptr<Toggle> toggle(Observable<bool>& state, const Modifier &mod = {});
    std::shared_ptr<Toggle> toggle(bool state, const Modifier &mod = {});

    std::shared_ptr<Input>  input(Observable<std::string>& text, const Modifier& mod = {});
    std::shared_ptr<Image>  image(const Texture& tex, const Modifier &mod = {});

    std::shared_ptr<Card>   card(const WidgetPtr& inner, const Modifier &mod = {});
    std::shared_ptr<Card>   card(const WidgetPtr& inner, CardType type = CardType::Filled, const Modifier &mod = {});

    std::shared_ptr<Checkbox>  checkbox(bool val, const Modifier &mod = {});
    std::shared_ptr<Checkbox>  checkbox(Observable<bool>& val, const Modifier &mod = {});

    std::shared_ptr<Column> column(const WidgetList& list, const Modifier &mod = {});
    std::shared_ptr<Row> row(const WidgetList& list, const Modifier &mod = {});
    std::shared_ptr<Box> box(const WidgetList& list, const Modifier &mod = {});

    std::shared_ptr<Row> radiobutton(const std::string& text, const Modifier& mod = {});
    std::shared_ptr<Row> radiobutton(const WidgetPtr& inner, const Modifier& mod = {});
    std::shared_ptr<RadioButton> radiobutton(const Modifier& mod = {}); // circle only

    std::shared_ptr<RadioGroup> radiogroup(
        Observable<int>& selected,
        const WidgetList& list,
        const Modifier& mod = {}
    );

    std::shared_ptr<RadioGroup> radiogroup(
        int selected,
        const WidgetList& list,
        const Modifier& mod = {}
    );
}

#endif //CIRCUITS_UI_H