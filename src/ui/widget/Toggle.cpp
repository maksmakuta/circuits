#include "Toggle.h"

#include "manager/ThemeManager.h"

namespace circuits {

    Toggle::Toggle(const bool state) : m_switch(state) {}

    glm::ivec2 Toggle::onMeasure(const glm::ivec2 &max) {
        return glm::ivec2{52,30};
    }

    void Toggle::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto rect = getRect();
        const auto radius = static_cast<float>(rect.size.y >> 1);

        r.rect(rect.pos,rect.size,radius);
        r.fill(m_switch ? theme.palette.surfaceVariant : theme.palette.primary);
        if (m_switch) {
            r.stroke(theme.palette.primary,theme.shape.borderThickness);
        }
        auto handle = rect.pos + rect.size / glm::ivec2{3,2};
        const auto handle_radius = radius * 0.75f;
        if (m_switch) {
            handle.x += rect.size.x / 3;
        }

        r.circle(handle,handle_radius);
        if (m_switch) {
            r.fill(theme.palette.primary);
        }else {
            r.fill(theme.palette.onPrimary);
        }
    }

    void Toggle::onEvent(const Event &e) {
        IWidget::onEvent(e);
        if (state() == State::Active) {
            m_switch = !m_switch;
        }
    }
}
