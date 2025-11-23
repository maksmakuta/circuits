#include "Label.h"

namespace circuits {

    Label::Label(std::string text) : IWidget(), m_text(std::move(text)) {}

    glm::ivec2 Label::onMeasure(const glm::ivec2 &max){
        const auto theme = currentTheme();
        return theme.font.textSize(m_text);
    }

    void Label::onLayout(const Rect& r){
        setRect(r);
    }

    void Label::onDraw(Renderer& r){
        const auto theme = currentTheme();
        r.setBaseline(Baseline::Bottom);
        r.text(theme.font,m_text,getRect().pos, theme.palette.text);

        // r.rect(getRect().pos, getRect().size);
        // r.stroke(theme.palette.border,theme.style.borderThickness);

    }


}
