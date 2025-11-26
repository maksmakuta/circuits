#include "Application.h"

#include <iostream>
#include <SDL3/SDL_events.h>

#include "graphics/Renderer.h"

namespace circuits {

    Application::Application() {

    }

    Theme Application::getTheme(){

    }

    ThemeName Application::getThemeName(){

    }

    void Application::switchTheme(){

    }

    void Application::setCursor(Cursor){

    }

    void Application::go(const std::shared_ptr<IScreen> &){

    }

    void Application::goBack(){

    }

    glm::ivec2 Application::screenSize(){

    }

    int Application::run() {
        m_window.swap();
        while (!m_window.isClosed()) {


            m_window.swap();
        }
        return 0;
    }

}
