#include "Row.h"

#include "utils/WidgetUtils.h"

namespace circuits {

    Row::Row(const WidgetList& list) : m_children(list), m_children_sizes(list.size(),{0,0}) {}

    glm::ivec2 Row::onMeasure(const glm::ivec2 &max) {
        auto size = glm::ivec2(0);

        for (auto i = 0; i < m_children.size(); ++i) {
            const auto& child = m_children[i];
            const auto child_size = WidgetUtils::preferredSize(
                child->getModifier().getParams(),
                WidgetUtils::sizeWithPadding(child, max),
                max
            );
            m_children_sizes[i] = child_size;
            size.y = glm::max(size.y, child_size.y);
            size.x += child_size.x;
        }

        return size;
    }

    void Row::onLayout(const Rect& r) {
        IWidget::onLayout(r);

        auto offset = getRect().pos;
        for (auto i = 0; i < m_children.size(); ++i) {
            const auto& child = m_children[i];
            const auto mod = child->getModifier();
            auto child_size = m_children_sizes[i];
            const auto g_offset = WidgetUtils::applyHGravity(
                mod.getGravity(),
                child_size,
                getRect().size
            );
            const auto rect = Rect(offset + g_offset, child_size);
            child->onLayout(WidgetUtils::removePadding(rect,mod.getPadding()));
            offset.x += child_size.x;
        }
    }

    void Row::onDraw(Renderer& r) {
        for (const auto& child : m_children) {
            child->onDraw(r);
        }
    }

    void Row::onUpdate(const float dt) {
        for (const auto& child : m_children) {
            child->onUpdate(dt);
        }
    }

    void Row::onEvent(const Event& e) {
        for (const auto& child : m_children) {
            child->onEvent(e);
        }
    }

}