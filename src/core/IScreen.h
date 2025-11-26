#ifndef CIRCUITS_ISCREEN_H
#define CIRCUITS_ISCREEN_H

#include "graphics/Renderer.h"
#include "window/Event.h"

namespace circuits {

    class IContext;

    class IScreen {
    public:
        explicit IScreen(const std::weak_ptr<IContext>& ctx) : m_context(ctx) {}
        virtual ~IScreen() = default;

        virtual void onInit() = 0;
        virtual void onDeinit() = 0;
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float) = 0;
        virtual void onEvent(const Event&) = 0;

        [[nodiscard]] std::shared_ptr<IContext> getContext() const {
            return m_context.lock();
        }

    private:
        std::weak_ptr<IContext> m_context;
    };

}

#endif //CIRCUITS_ISCREEN_H