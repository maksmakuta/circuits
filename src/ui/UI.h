#ifndef CIRCUITS_UI_H
#define CIRCUITS_UI_H

#include "layout/Column.h"
#include "layout/Row.h"

#include "widget/Button.h"
#include "widget/Card.h"
#include "widget/Image.h"
#include "widget/Input.h"
#include "widget/Label.h"
#include "widget/Toggle.h"

namespace circuits {

    std::shared_ptr<Label>  label(const std::string& text, const FontRole& r = FontRole::Body, const Modifier &mod = {});
    std::shared_ptr<Label>  label(const std::string& text, const Modifier &mod = {});

    std::shared_ptr<Button> button(const WidgetPtr& inner, const Modifier &mod = {});
    std::shared_ptr<Button> button(const std::string &text, const Modifier &mod = {});

    std::shared_ptr<Input>  input(const std::string& text, const Modifier& mod = {});
    std::shared_ptr<Toggle> toggle(bool state, const Modifier &mod = {});
    std::shared_ptr<Image>  image(const Texture& tex, const Modifier &mod = {});

    std::shared_ptr<Card>   card(const WidgetPtr& inner, const Modifier &mod = {});
    WidgetPtr tooltip(WidgetPtr inner, Modifier mod = {});
    WidgetPtr notification(std::string message, Modifier mod = {});

    std::shared_ptr<Column> column(const WidgetList& list, const Modifier &mod = {});
    std::shared_ptr<Row> row(const WidgetList& list, const Modifier &mod = {});
    WidgetPtr grid(const WidgetList& list, Modifier mod = {});
    WidgetPtr box(const WidgetList& list, Modifier mod = {});

}

#endif //CIRCUITS_UI_H