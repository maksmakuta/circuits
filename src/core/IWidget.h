#ifndef CIRCUITS_IWIDGET_H
#define CIRCUITS_IWIDGET_H

#include <memory>

#include "Rect.h"

#include "graphics/Renderer.h"
#include "Modifier.h"
#include "window/Event.h"

namespace circuits {

    class IWidget {
    public:
        virtual ~IWidget() = default;

        virtual glm::ivec2 onMeasure(const glm::ivec2& max) = 0;
        virtual void onLayout(const Rect&) = 0;
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float){}
        virtual void onEvent(const Event&){}

        void setModifier(const Modifier& m) {
            m_modifier = m;
        }

        void setRect(const Rect& r) {
            m_rect = r;
        }

        [[nodiscard]] Modifier getModifier() const {
            return m_modifier;
        }

        [[nodiscard]] Rect getRect() const {
            return m_rect;
        }

    private:
        Modifier m_modifier;
        Rect m_rect;
    };

    using WidgetPtr = std::shared_ptr<IWidget>;

}

#endif //CIRCUITS_IWIDGET_H