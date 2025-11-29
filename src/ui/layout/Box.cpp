#include "Box.h"

#include "utils/WidgetUtils.h"

namespace circuits {

    Box::Box(const WidgetList& list) : m_children(list), m_children_sizes(list.size(),{0,0}) {}
    Box::~Box() = default;

    glm::ivec2 Box::onMeasure(const glm::ivec2 &max){
        auto size = glm::ivec2(0);

        for (auto i = 0; i < m_children.size(); ++i) {
            const auto& child = m_children[i];
            const auto child_size = WidgetUtils::preferredSize(
                child->getModifier().getParams(),
                WidgetUtils::sizeWithPadding(child, max),
                max
            );
            m_children_sizes[i] = child_size;
            size = glm::max(size, child_size);
        }

        return size;
    }

    void Box::onLayout(const Rect &r){
        IWidget::onLayout(r);

        const auto offset = getRect().pos;
        for (auto i = 0; i < m_children.size(); ++i) {
            const auto& child = m_children[i];
            const auto mod = child->getModifier();
            auto child_size = m_children_sizes[i];
            const auto g_offset = WidgetUtils::applyGravity(
                mod.getGravity(),
                child_size,
                getRect().size
            );
            const auto rect = Rect(offset + g_offset, child_size);
            child->onLayout(WidgetUtils::removePadding(rect,mod.getPadding()));
        }
    }

    void Box::onDraw(Renderer& r){
        r.rect(getRect().pos, getRect().size);
        r.fill(Color(0xFFFF0000));


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
