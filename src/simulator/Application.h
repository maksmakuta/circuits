#ifndef CIRCUITS_APPLICATION_H
#define CIRCUITS_APPLICATION_H

#include "base/Context.h"
#include "graphics/Renderer.h"
#include "screen/MainScreen.h"
#include "window/Window.h"

namespace circuits {

    class Application {
    public:
        Application();

        int run();

    private:
        void onUpdate(float dt);
        void onDraw();
        void onEvent(const Event&);

        Window m_window;
        Renderer m_renderer;
        MainScreen m_screen;
        ContextPtr m_context = nullptr;
    };

}

#endif //CIRCUITS_APPLICATION_H