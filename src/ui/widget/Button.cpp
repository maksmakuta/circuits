#include "Button.h"

#include <utility>

#include "ui/theme/ThemeManager.h"

namespace circuits {

    Button::Button(WidgetPtr p) : IWidget(), m_inner(std::move(p)){}

    glm::ivec2 Button::onMeasure(const glm::ivec2 &max) {
        if (!m_inner)
            return glm::ivec2{10, 10};

        const auto padding = getModifier().getPadding();
        const glm::ivec2 innerMax = {
            max.x - padding.left - padding.right,
            max.y - padding.top  - padding.bottom
        };

        const auto mod = m_inner->getModifier();
        const glm::ivec2 innerSize = m_inner->onMeasure(innerMax);
        return getModifier().applySize(mod.applyPadding(innerSize), max);
    }

    void Button::onLayout(const Rect& r) {
        IWidget::onLayout(r);

        if (!m_inner) return;

        const auto padding = m_inner->getModifier().getPadding();
        const auto gravity = m_inner->getModifier().getGravity();

        const glm::ivec2 innerMax = {
            r.size.x - padding.left - padding.right,
            r.size.y - padding.top  - padding.bottom
        };

        glm::ivec2 innerSize = m_inner->onMeasure(innerMax);

        glm::ivec2 offset = {
            r.pos.x + padding.left,
            r.pos.y + padding.top
        };

        if (gravity == Gravity::Center) {
            offset.x += (innerMax.x - innerSize.x) / 2;
            offset.y += (innerMax.y - innerSize.y) / 2;
        } else if (gravity == Gravity::Right) {
            offset.x += innerMax.x - innerSize.x;
        }

        m_inner->onLayout({offset, innerSize});
    }

    void Button::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto& [pos, size] = getRect();
        r.rect(pos,size,theme.shape.cornerMedium);
        r.fill(theme.palette.primary);
        if (state() == State::Hover) {
            r.stroke(theme.palette.outline,theme.shape.borderThickness);
        }else if (state() == State::Active) {
            r.fill(theme.palette.secondary);
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
