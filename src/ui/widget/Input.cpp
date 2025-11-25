#include "Input.h"

#include <utility>

#include "ui/theme/ThemeManager.h"

namespace circuits {

    Input::Input(std::string t) : m_text(std::move(t)) {
        setAppearance(Appearance::SurfaceVariant);
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

}
