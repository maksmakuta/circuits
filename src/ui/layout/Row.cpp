#include "Row.h"

namespace circuits {

    Row::Row(const WidgetList& list) : m_children(list), m_children_sizes(list.size(),{0,0}) {}

    glm::ivec2 Row::onMeasure(const glm::ivec2 &max) {
        return {0, 0};
    }

    void Row::onLayout(const Rect& r) {
        setRect(r);
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