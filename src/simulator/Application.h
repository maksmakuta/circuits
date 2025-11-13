#ifndef CIRCUITS_APPLICATION_H
#define CIRCUITS_APPLICATION_H

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
        MainScreen m_screen;
        Renderer m_renderer;
    };

}

#endif //CIRCUITS_APPLICATION_H