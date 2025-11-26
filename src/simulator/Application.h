#ifndef CIRCUITS_APPLICATION_H
#define CIRCUITS_APPLICATION_H

#include <stack>

#include "core/IContext.h"
#include "window/Window.h"

namespace circuits {

    class Application final : public IContext, public std::enable_shared_from_this<IContext>{
    public:
        Application();

        int run();

        void setCursor(Cursor) override;
        void go(const std::shared_ptr<IScreen> &) override;
        void goBack() override;
        glm::ivec2 screenSize() override;

    private:
        glm::ivec2 m_view{0};
        Window m_window;
        Renderer m_renderer;
        std::stack<std::shared_ptr<IScreen>> m_nav_stack;
    };

}

#endif //CIRCUITS_APPLICATION_H