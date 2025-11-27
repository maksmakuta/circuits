#include "Input.h"

#include <utility>

namespace circuits {

    Input::Input(Observable<std::string> &text) : m_text(text.getValue()){
        setAppearance(Appearance::SurfaceVariant);
        text.observe([this](const std::string& val) {
            setText(val);
        });
    }

    glm::ivec2 Input::onMeasure(const glm::ivec2 &max) {
        return currentTheme().typography.body.textSize(m_text) + 24;
    }

    void Input::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto rect = getRect();

        r.rect(rect.pos,rect.size, theme.shape.cornerSmall);
        r.fill(theme.palette.surfaceVariant);
        if (state() == State::Active) {
            r.stroke(theme.palette.outline,theme.shape.borderThickness);
        }

        r.text(theme.typography.body, m_text, rect.pos + 12, theme.palette.onSurfaceVariant);
    }

    void Input::onEvent(const Event &e) {
        IWidget::onEvent(e);
    }

    void Input::setText(const std::string& text) {
        m_text = text;
    }

    std::string Input::getText() const {
        return m_text;
    }

}
