#ifndef CIRCUITS_APPLICATION_H
#define CIRCUITS_APPLICATION_H

#include <memory>

#include "core/IScreen.h"
#include "graphics/Renderer.h"
#include "window/Window.h"

namespace circuits {

    class Application {
    public:
        Application();

        int run();
    private:
        void pollEvents();
        void updateDelta();

        uint64_t lastTime = 0;
        Window m_window;
        Renderer m_renderer;
        std::unique_ptr<IScreen> m_screen;
    };

}

#endif //CIRCUITS_APPLICATION_H