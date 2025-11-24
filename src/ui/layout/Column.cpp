#include "Column.h"

namespace circuits {

    Column::Column(const WidgetList& list) : IWidget(), m_children(list), m_children_sizes(list.size(),{0,0}) {}

    glm::ivec2 Column::onMeasure(const glm::ivec2 &max) {
        auto size = glm::ivec2(0);
        for (auto i = 0; i < m_children.size(); i++) {
            const auto& child = m_children[i];
            //const auto mod = child->getModifier();
            const auto child_content = child->onMeasure(max);
            size.x = std::max(size.x, child_content.x);
            size.y += child_content.y;
            m_children_sizes[i] = child_content;
        }
        return size;
    }

    void Column::onLayout(const Rect& r) {
        setRect(r);
        auto offset = r.pos;
        for (auto i = 0; i < m_children.size(); i++) {
            const auto size = m_children_sizes[i];
            m_children[i]->onLayout({offset, size});
            offset.y += size.y;
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