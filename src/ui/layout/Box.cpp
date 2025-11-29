#include "Box.h"

namespace circuits {

    Box::Box(const WidgetList& list) : m_children(list), m_children_sizes(list.size(),{0,0}) {}
    Box::~Box() = default;

    glm::ivec2 Box::onMeasure(const glm::ivec2 &max){
       return {0,0};
    }

    void Box::onLayout(const Rect &r){
        IWidget::onLayout(r);
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