#include "Label.h"

#include <utility>

namespace circuits {

    Label::Label(std::string t, const Modifier& m) : IWidget(m), m_text(std::move(t)){}

    glm::ivec2 Label::onMeasure(const glm::ivec2 &max_size){
        return getContext()->getFont().textSize(m_text);
    }

    void Label::onDraw(Renderer& r){
        // this for layout debug (temporary code)
        r.rect(m_rect.pos,m_rect.size);
        r.stroke(Color(0xFF00FF00),1);

        r.text(
            getContext()->getFont(),
            m_text,
            m_rect.pos + glm::ivec2{0,getContext()->getFont().getSize()},
            getContext()->getTheme()->text);
    }

    void Label::setText(const std::string& t) {
        m_text = t;
    }

    std::string Label::getText() const {
        return m_text;
    }

}