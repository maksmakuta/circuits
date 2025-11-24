#include "Button.h"

#include <utility>

namespace circuits {

    Button::Button(WidgetPtr p) : IWidget(), m_inner(std::move(p)){}

    glm::ivec2 Button::onMeasure(const glm::ivec2 &max) {
        return m_inner ? m_inner->onMeasure(max) : glm::ivec2(100,50);
    }

    void Button::onLayout(const Rect& r) {
        setRect(r);
        if (m_inner) {
            m_inner->onLayout(r);
        }
    }

    void Button::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto& [pos, size] = getRect();
        r.rect(pos,size,theme.style.cornerRadius);
        if (state() == State::Hover) {
            r.stroke(theme.palette.border,theme.style.borderThickness);
        }else if (state() == State::Active) {
            r.fill(theme.palette.primary);
        }else {
            r.fill(theme.palette.surface);
        }

        if (m_inner) {
            m_inner->onDraw(r);
        }
    }

    void Button::onUpdate(const float dt) {
        if (m_inner) {
            m_inner->onUpdate(dt);
        }
    }

    void Button::onEvent(const Event& e) {
        IWidget::onEvent(e);
        if (m_inner) {
            m_inner->onEvent(e);
        }
    }

}