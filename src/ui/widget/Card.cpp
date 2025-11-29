#include "Card.h"

#include <utility>

#include "utils/ColorUtils.h"
#include "utils/WidgetUtils.h"

namespace circuits {

    Card::Card(WidgetPtr w, const CardType t) : m_type(t), m_inner(std::move(w)) {
        setAppearance(t == CardType::Filled ? Appearance::SurfaceVariant : Appearance::Surface);
    }

    glm::ivec2 Card::onMeasure(const glm::ivec2 &max) {
        auto size = glm::ivec2(0);

        if(m_inner != nullptr) {
            if (m_inner->getParent() != shared_from_this()) {
                m_inner->setParent(shared_from_this());
            }

            const auto& child = m_inner;
            const auto child_size = WidgetUtils::preferredSize(
                child->getModifier().getParams(),
                WidgetUtils::sizeWithPadding(child, max),
                max
            );
            m_child_size = child_size;
            size = glm::max(size, child_size);
        } else {
            size += glm::ivec2{50,30};
        }

        return size;
    }

    void Card::onLayout(const Rect &r) {
        IWidget::onLayout(r);

        if(m_inner == nullptr) return;

        const auto offset = getRect().pos;
        const auto& child = m_inner;
        const auto mod = child->getModifier();
        const auto& child_size = m_child_size;
        const auto g_offset = WidgetUtils::applyGravity(
            mod.getGravity(),
            child_size,
            getRect().size
        );
        const auto rect = Rect(offset + g_offset, child_size);
        child->onLayout(WidgetUtils::removePadding(rect,mod.getPadding()));
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
