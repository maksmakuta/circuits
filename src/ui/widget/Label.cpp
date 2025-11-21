#include "Label.h"

#include <utility>

namespace circuits {

    Label::Label(std::string t) : IWidget(), m_text(std::move(t)){}

    glm::ivec2 Label::onMeasure(const glm::ivec2 &max_size){
        return getContext()->font.textSize(m_text);
    }

    void Label::onDraw(Renderer& r){
        // this for layout debug (temporary code)
        r.rect(m_pos,m_size);
        r.stroke(Color(0xFF00FF00),1);

        r.text(
            getContext()->font,
            m_text,
            m_pos + glm::ivec2{0,getContext()->font.getSize()},
            getContext()->theme->text);
    }

    void Label::setText(const std::string& t) {
        m_text = t;
    }

    std::string Label::getText() const {
        return m_text;
    }

}