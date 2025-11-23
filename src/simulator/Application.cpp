#include "Application.h"

#include "screen/MainScreen.h"

namespace circuits {

    Application::Application() {
        m_screen = std::make_unique<MainScreen>();
    }

    void Application::pollEvents() {
        Event e;
        while (Window::poll(e)) {
            m_screen->onEvent(e);
            if (e.type == EventType::WindowClose) {
                m_window.close();
            }
        }
    }

    void Application::updateDelta() {
        const auto now = Window::getTime();
        const auto delta = static_cast<float>(now - lastTime) / 1000.f;
        m_screen->onUpdate(delta);
        lastTime = now;
    }

    int Application::run() {
        m_window.swap();
        m_renderer.load();
        m_screen->onInit();
        while (!m_window.isClosed()) {
            updateDelta();
            pollEvents();

            m_renderer.begin();
            m_screen->onDraw(m_renderer);
            m_renderer.end();

            m_window.swap();
        }
        m_renderer.unload();
        m_screen->onDeinit();
        return 0;
    }

}
