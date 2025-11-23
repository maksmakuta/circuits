#ifndef CIRCUITS_IWIDGET_H
#define CIRCUITS_IWIDGET_H

#include "base/Context.h"
#include "base/Rect.h"
#include "graphics/Renderer.h"
#include "ui/Modifier.h"
#include "window/Event.h"

namespace circuits {

    class IWidget {
    public:
        explicit IWidget(const Modifier& m = {}) : m_modifier(m) {}
        virtual ~IWidget() = default;

        virtual glm::ivec2 onMeasure(const glm::ivec2& parent_size) = 0;
        virtual void onLayout(const Rect& r) {
            m_rect = r;
        }
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float dt){}
        virtual void onEvent(const Event&) {}

        void setContext(const ContextPtr& ctx) {
            m_context = ctx;
        }

        [[nodiscard]] ContextPtr getContext() const {
            return m_context;
        }

        [[nodiscard]] Modifier getModifier() const {
            return m_modifier;
        }

    protected:
        ContextPtr m_context;
        Modifier m_modifier;
        Rect m_rect;
        uint32_t m_flags{0};
    };

    using WidgetPtr = std::shared_ptr<IWidget>;

}

#endif //CIRCUITS_IWIDGET_H