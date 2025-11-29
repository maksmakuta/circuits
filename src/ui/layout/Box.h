#ifndef CIRCUITS_BOX_H
#define CIRCUITS_BOX_H

#include "core/IWidget.h"

namespace circuits {

    class Box final : public IWidget, public std::enable_shared_from_this<Box>{
    public:
        Box(const WidgetList& list = {});
        ~Box() override;

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onLayout(const Rect &r) override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &e) override;
    private:
        std::vector<WidgetPtr> m_children;
        std::vector<glm::ivec2> m_children_sizes;
    };

}

#endif //CIRCUITS_BOX_H