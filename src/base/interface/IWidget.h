#ifndef CIRCUITS_IWIDGET_H
#define CIRCUITS_IWIDGET_H

#include "base/Rect.h"
#include "graphics/Renderer.h"
#include "window/Event.h"

namespace circuits {

    class IWidget {
    public:
        virtual ~IWidget() = default;

        virtual glm::vec2 onMeasure(const Size&) = 0;
        virtual void onLayout(const Rect&) = 0;
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float dt) = 0;
        virtual void onEvent(const Event& e) = 0;
    };

}

#endif //CIRCUITS_IWIDGET_H