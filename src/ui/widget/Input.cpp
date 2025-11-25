#include "Input.h"

#include <utility>

namespace circuits {

    Input::Input(std::string t) : IWidget(), m_text(std::move(t)){}

    glm::ivec2 Input::onMeasure(const glm::ivec2 &max) {
        /*
        return currentTheme().font.textSize(m_text) + 16;
        */
        return {};
    }

    void Input::onDraw(Renderer& r) {/*
        const auto theme = currentTheme();
        const auto rect = getRect();

        r.rect(rect.pos,rect.size, theme.style.borderRadius);
        r.fill(theme.palette.surface);
        r.stroke(theme.palette.border,theme.style.borderThickness);

        r.text(theme.font, m_text, rect.pos + 8, theme.palette.text);
        */
    }

    void Input::onEvent(const Event &e) {
        IWidget::onEvent(e);
    }

}