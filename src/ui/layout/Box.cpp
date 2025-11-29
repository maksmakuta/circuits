#include "Box.h"

namespace circuits {

    Box::Box(const WidgetList& list) : m_children(list), m_children_sizes(list.size(),{0,0}) {}
    Box::~Box() = default;

    glm::ivec2 Box::onMeasure(const glm::ivec2 &max){
        auto size = glm::ivec2{0};
        for (auto i = 0; i < m_children.size(); i++) {
            const auto& child = m_children[i];
            setAppearance(getParent() ? getParent()->getAppearance() : getAppearance());
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

            size = glm::max(size, measured);
        }
        return size;
    }

    void Box::onLayout(const Rect &r){
        IWidget::onLayout(r);
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
                r.pos.x + padding.left,
                r.pos.y + padding.top
            };

            glm::ivec2 finalSize = size;

            const int freeX = r.size.x - size.x;
            const int freeY = r.size.y - size.y;

            if (any(gravity, Gravity::HCenter))
                finalPos.x = r.pos.x + freeX / 2 - padding.right;
            else if (any(gravity, Gravity::Right))
                finalPos.x = r.pos.x + freeX  - padding.right;

            if (any(gravity, Gravity::VCenter))
                finalPos.y = r.pos.y + freeY / 2 - padding.bottom;
            else if (any(gravity, Gravity::Bottom))
                finalPos.y = r.pos.y + freeY - padding.bottom;

            child->onLayout({finalPos, finalSize});
        }
    }

    void Box::onDraw(Renderer& r){
        for (const auto& child : m_children) {
            child->onDraw(r);
        }
    }

    void Box::onUpdate(const float dt){
        for (const auto& child : m_children) {
            child->onUpdate(dt);
        }
    }

    void Box::onEvent(const Event &e){
        for (const auto& child : m_children) {
            child->onEvent(e);
        }
    }

}