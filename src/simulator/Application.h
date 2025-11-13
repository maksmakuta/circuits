#ifndef CIRCUITS_APPLICATION_H
#define CIRCUITS_APPLICATION_H

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
    };

}

#endif //CIRCUITS_APPLICATION_H