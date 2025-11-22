#include "Button.h"

#include <utility>

namespace circuits {

    Button::Button(WidgetPtr inner, ButtonCallback callback, const Modifier& m)
        : IWidget(m), m_inner(std::move(inner)), m_callback(std::move(callback)) {}

    glm::ivec2 Button::onMeasure(const glm::ivec2 &max_size) {
        if (m_inner) {
            m_inner->setContext(getContext());
            return m_inner->onMeasure(max_size);
        }
        return glm::ivec2(50);
    }

    void Button::onLayout(const Rect &r) {
        IWidget::onLayout(r);
        if (m_inner) {
            m_inner->onLayout(r);
        }
    }

    void Button::onDraw(Renderer& r) {
        r.rect(m_rect.pos,m_rect.size);
        r.fill(getContext()->getTheme()->primary);
        if (is_hovered) {
            r.stroke(getContext()->getTheme()->text,4);
        }

        if (m_inner) {
            m_inner->onDraw(r);
        }
    }

    void Button::onEvent(const Event &event) {
        IWidget::onEvent(event);

        if(event.type == EventType::MouseMove) {
            const auto mouse = glm::ivec2(event.mouseMove.x, event.mouseMove.y);
            is_hovered = m_rect.contains(mouse);
        }else {
            is_hovered = false;
        }

        if (event.type == EventType::MouseDown) {
            const auto mouse = glm::ivec2(event.mouseMove.x, event.mouseMove.y);
            if (m_rect.contains(mouse) && m_callback) {
                m_callback();
            }
        }
    }
}
