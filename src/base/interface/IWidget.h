#ifndef CIRCUITS_IWIDGET_H
#define CIRCUITS_IWIDGET_H

#include "base/Context.h"
#include "graphics/Renderer.h"
#include "window/Event.h"

namespace circuits {

    class IWidget {
    public:
        virtual ~IWidget() = default;

        virtual glm::ivec2 onMeasure(const glm::ivec2& max_size) = 0;
        virtual void onLayout(const glm::ivec2& pos, const glm::ivec2& size) {
            m_pos = pos;
            m_size = size;
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

    protected:
        ContextPtr m_context;
        glm::ivec2 m_pos{0};
        glm::ivec2 m_size{0};
        uint32_t m_flags{0};
    };

}

#endif //CIRCUITS_IWIDGET_H