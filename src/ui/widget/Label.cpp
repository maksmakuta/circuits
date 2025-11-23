#include "Label.h"

namespace circuits {

    Label::Label(std::string text) : IWidget(), m_text(std::move(text)) {}

    glm::ivec2 Label::onMeasure(const glm::ivec2 &max){

    }

    void Label::onLayout(const Rect& r){

    }

    void Label::onDraw(Renderer& r){

    }


}