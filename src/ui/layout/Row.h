#ifndef CIRCUITS_ROW_H
#define CIRCUITS_ROW_H

#include "core/IWidget.h"

namespace circuits {

    class Row final : public IWidget, public std::enable_shared_from_this<Row>{
    public:
        Row(const WidgetList& list);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onLayout(const Rect &) override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &) override;

    private:
        std::vector<WidgetPtr> m_children;
        std::vector<glm::ivec2> m_children_sizes;
    };
}

#endif //CIRCUITS_ROW_H