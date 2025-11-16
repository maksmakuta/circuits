#include "Application.h"

namespace circuits {

    Application::Application() : m_window("Circuits", glm::ivec2{800,600}), m_screen(MainScreen()){}

    int Application::run() {
        m_renderer.load();
        m_screen.onInit();
        auto last_tile = Window::getTime();
        while (!m_window.isClosed()) {
            const auto now = Window::getTime();
            onUpdate(static_cast<float>(now - last_tile) / 1000.f);
            last_tile = now;

            Event e;
            while(Window::poll(e)) {
                onEvent(e);
            }
            m_renderer.begin();
            onDraw();
            m_renderer.end();

            m_window.swap();
        }
        m_screen.onDeinit();
        m_renderer.unload();
        return 0;
    }

    void Application::onUpdate(const float dt) {
        m_screen.onUpdate(dt);
    }

    void Application::onDraw() {
        m_screen.onDraw(m_renderer);
    }

    void Application::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_renderer.resize(glm::ivec2{e.window.width, e.window.height});
        }
        if (e.type == EventType::WindowClose) {
            m_window.close();
        }
        m_screen.onEvent(e);
    }

}
