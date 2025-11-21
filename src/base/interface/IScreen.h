#ifndef CIRCUITS_ISCREEN_H
#define CIRCUITS_ISCREEN_H

#include "graphics/Renderer.h"
#include "window/Event.h"
#include "base/Context.h"

namespace circuits {

    template<class VM>
    class IScreen {
        static_assert(std::is_base_of_v<IViewmodel, VM>, "VM must inherit from IViewModel");
    public:
        template<typename... Args>
        explicit IScreen(Args&&... args) : m_viewmodel(std::make_unique<VM>(std::forward<Args>(args)...)) {}

        virtual ~IScreen() = default;

        virtual void onInit() = 0;
        virtual void onDeinit() = 0;
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float dt) = 0;
        virtual void onEvent(const Event&) = 0;

        VM& viewmodel() { return *m_viewmodel; }
        const VM& viewmodel() const { return *m_viewmodel; }

        void setContext(const std::shared_ptr<Context>& inContext) {
            m_context = inContext;
        }

        [[nodiscard]] const std::shared_ptr<Context>& getContext() const {
            return m_context;
        }

    private:
        ContextPtr m_context = nullptr;
        std::unique_ptr<VM> m_viewmodel = nullptr;
    };

}

#endif //CIRCUITS_ISCREEN_H