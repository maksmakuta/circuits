#ifndef CIRCUITS_IWIDGET_H
#define CIRCUITS_IWIDGET_H

#include "graphics/Renderer.h"
#include "window/Event.h"

namespace circuits {

    class IWidget {
    public:
        virtual ~IWidget() = default;

        virtual glm::ivec2 onMeasure(const glm::ivec2& max_size) = 0;
        virtual void onLayout(const glm::ivec2& pos, const glm::ivec2& size) = 0;
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float dt) = 0;
        virtual void onEvent(const Event&) {}

    protected:
        glm::ivec2 pos{0};
        glm::ivec2 size{0};
        uint32_t flags{0};
    };

}

#endif //CIRCUITS_IWIDGET_H