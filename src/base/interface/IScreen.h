#ifndef CIRCUITS_ISCREEN_H
#define CIRCUITS_ISCREEN_H

#include "graphics/Renderer.h"
#include "window/Event.h"
#include "base/Context.h"

namespace circuits {

    class IScreen {
    public:
        virtual ~IScreen() = default;

        virtual void onInit() = 0;
        virtual void onDeinit() = 0;
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float dt) = 0;
        virtual void onEvent(const Event&) = 0;

        void setContext(const std::shared_ptr<Context>& inContext) {
            m_context = inContext;
        }

        const std::shared_ptr<Context>& getContext() {
            return m_context;
        }

    private:
        ContextPtr m_context = nullptr;
    };

}

#endif //CIRCUITS_ISCREEN_H