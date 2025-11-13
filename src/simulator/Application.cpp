#include "Application.h"

#include <format>
#include <iostream>

#include "glad/gl.h"
#include "graphics/Color.h"

namespace circuits {

    const auto COLOR = Color(0xFFF09819);

    Application::Application() : m_window("Circuits", glm::ivec2{800,600}){}

    int Application::run() {
        auto last_tile = Window::getTime();
        while (!m_window.isClosed()) {
            const auto now = Window::getTime();
            onUpdate(static_cast<float>(now - last_tile) / 1000.f);
            last_tile = now;

            Event e;
            while(Window::poll(e)) {
                onEvent(e);
                if (e.type == EventType::WindowClose) {
                    m_window.close();
                }
            }

            onDraw();

            m_window.swap();
        }
        return 0;
    }

    void Application::onUpdate(const float dt) {
        std::cout << std::format("{:0.2f} fps",1.0 / dt) << std::endl;
    }

    void Application::onDraw() {
        glClearColor(COLOR.r(),COLOR.g(),COLOR.b(),COLOR.a());
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Application::onEvent(const Event& e) {

    }

}
