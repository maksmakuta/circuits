#include "Column.h"

namespace circuits {

    Column::Column(const WidgetList& list) : m_children(list), m_children_sizes(list.size(),{0,0}) {}

    glm::ivec2 Column::onMeasure(const glm::ivec2 &max) {
        glm::ivec2 size = {0, 0};

        setAppearance(getParent() ? getParent()->getAppearance() : getAppearance());

        for (size_t i = 0; i < m_children.size(); i++) {
            const auto& child = m_children[i];

            child->setParent(shared_from_this());

            const auto mod = child->getModifier();
            const auto padding = mod.getPadding();

            glm::ivec2 innerMax = {
                max.x - padding.left - padding.right,
                max.y - padding.top  - padding.bottom
            };

            glm::ivec2 measured = child->onMeasure(innerMax);
            measured = mod.applySize(measured, innerMax);
            measured = mod.applyPadding(measured);

            m_children_sizes[i] = measured;

            size.x = std::max(size.x, measured.x);
            size.y += measured.y;
        }

        return getModifier().applySize(size, max);
    }

    void Column::onLayout(const Rect& r) {
        setRect(r);
        glm::ivec2 cursor = r.pos;

        for (size_t i = 0; i < m_children.size(); i++) {
            const auto& child = m_children[i];
            const auto mod = child->getModifier();
            const auto padding = mod.getPadding();
            const auto gravity = mod.getGravity();

            auto size = m_children_sizes[i];

            if (mod.getParams().width.unit == SizeUnit::Fill) {
                size.x = getRect().size.x;
            }
            if (mod.getParams().height.unit == SizeUnit::Fill) {
                size.y = getRect().size.y;
            }

            glm::ivec2 finalPos = {
                cursor.x + padding.left,
                cursor.y + padding.top
            };

            glm::ivec2 finalSize = {
                size.x - padding.left - padding.right,
                size.y - padding.top  - padding.bottom
            };

            const int freeX = r.size.x - size.x;
            if (gravity == Gravity::Center)
                finalPos.x = r.pos.x + freeX / 2 + padding.left;
            else if (gravity == Gravity::Right)
                finalPos.x = r.pos.x + freeX + padding.left;

            child->onLayout({finalPos, finalSize});
            cursor.y += size.y;
        }
    }

    void Column::onDraw(Renderer& r) {
        for (const auto& child : m_children) {
            child->onDraw(r);
        }
        // const auto theme = currentTheme();
        // r.rect(getRect().pos, getRect().size);
        // r.stroke(theme.palette.border,theme.style.borderThickness);
    }

    void Column::onUpdate(const float dt) {
        for (const auto& child : m_children) {
            child->onUpdate(dt);
        }
    }

    void Column::onEvent(const Event& e) {
        for (const auto& child : m_children) {
            child->onEvent(e);
        }
    }

}