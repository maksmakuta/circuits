#include "Column.h"

namespace circuits {

    Column::Column(const std::initializer_list<WidgetPtr>& list, const Modifier& m) : IWidget(m), m_widgets(list.begin(), list.end()) {}

    glm::ivec2 Column::onMeasure(const glm::ivec2 &max_size) {
        auto size = glm::ivec2{0};
        for (const auto& widget : m_widgets) {
            if (widget) {
                widget->setContext(getContext());
                const auto w_size = widget->onMeasure(max_size);
                size.x = std::max(w_size.x,size.x);
                size.y += w_size.y;
            }
        }
        return size;
    }

    void Column::onLayout(const Rect &rect) {
        IWidget::onLayout(rect);

        auto offset = glm::ivec2{rect.pos};
        for (const auto& widget : m_widgets) {
            if (widget) {
                widget->setContext(getContext());
                const auto w_size = widget->onMeasure(rect.size);
                widget->onLayout({offset, w_size});
                offset.y += w_size.y;
            }
        }

    }

    void Column::onDraw(Renderer& r) {
        // this for layout debug (temporary code)
        r.rect(m_rect.pos,m_rect.size);
        r.stroke(Color(0xFFFF0000),2);

        for (const auto &widget : m_widgets) {
            if (widget) {
                widget->onDraw(r);
            }
        }
    }

    void Column::onEvent(const Event &event) {
        IWidget::onEvent(event);
        for (const auto &widget : m_widgets) {
            if (widget) {
                widget->onEvent(event);
            }
        }
    }
}
