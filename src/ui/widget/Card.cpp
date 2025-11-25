#include "Card.h"

#include <utility>

#include "ui/theme/ThemeManager.h"

namespace circuits {

    Card::Card(WidgetPtr w) : m_inner(std::move(w)) {
        setAppearance(Appearance::Surface);
    }

    glm::ivec2 Card::onMeasure(const glm::ivec2 &max) {
        if (!m_inner)
            return glm::ivec2{60, 30};

        m_inner->setParent(shared_from_this());

        const auto padding = getModifier().getPadding();
        const glm::ivec2 innerMax = {
            max.x - padding.left - padding.right,
            max.y - padding.top  - padding.bottom
        };

        const auto mod = m_inner->getModifier();
        const glm::ivec2 innerSize = m_inner->onMeasure(innerMax);
        const glm::ivec2 size = mod.applyPadding(innerSize);

        return getModifier().applySize(size, max);
    }

    void Card::onLayout(const Rect &r) {
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

    void Card::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        r.rect(getRect().pos,getRect().size, theme.shape.cornerMedium);
        r.fill(theme.palette.surface);

        if (m_inner) {
            m_inner->onDraw(r);
        }
    }

    void Card::onUpdate(const float dt) {
        if (m_inner) {
            m_inner->onUpdate(dt);
        }
    }

    void Card::onEvent(const Event &e) {
        if (m_inner) {
            m_inner->onEvent(e);
        }
    }



}
