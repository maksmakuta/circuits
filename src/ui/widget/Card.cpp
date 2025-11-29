#include "Card.h"

#include <utility>

#include "utils/ColorUtils.h"

namespace circuits {

    Card::Card(WidgetPtr w, const CardType t) : m_type(t), m_inner(std::move(w)) {
        setAppearance(t == CardType::Filled ? Appearance::SurfaceVariant : Appearance::Surface);
    }

    glm::ivec2 Card::onMeasure(const glm::ivec2 &max) {
        if (!m_inner)
            return glm::ivec2{60, 30};
        return {0,0};
    }

    void Card::onLayout(const Rect &r) {
        IWidget::onLayout(r);
        if (!m_inner) return;
        m_inner->onLayout(r);
    }

    void Card::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        r.rect(getRect().pos,getRect().size, theme.shape.cornerMedium);
        r.fill(ColorUtils::resolveColor(getAppearance(),state()));
        if (m_type == CardType::Outlined) {
            r.stroke(theme.palette.outline,1);
        }

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
