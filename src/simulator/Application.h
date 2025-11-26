#ifndef CIRCUITS_APPLICATION_H
#define CIRCUITS_APPLICATION_H

#include <string>

#include "window/Window.h"

namespace circuits {

    class Application {
    public:
        Application();

        int run();
    private:
        void pollEvents();
        void updateDelta();

        bool m_text_input{false};
        std::string m_text;
        Window m_window;
    };

}

#endif //CIRCUITS_APPLICATION_H