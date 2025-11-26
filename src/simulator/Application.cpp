#include "Application.h"

#include "graphics/Renderer.h"
#include "screen/MainScreen.h"

namespace circuits {

    Application::Application() = default;


    void Application::setCursor(const Cursor c){
        m_window.setCursor(c);
    }

    void Application::go(const std::shared_ptr<IScreen>& s){
        if (s == nullptr) { return; }
        m_nav_stack.push(s);
        m_nav_stack.top()->onInit();
    }

    void Application::goBack(){
        if (m_nav_stack.size() > 1) {
            m_nav_stack.top()->onDeinit();
            m_nav_stack.pop();
        }
    }

    glm::ivec2 Application::screenSize(){
        return m_view;
    }

    int Application::run() {
        setTheme(Theme::getTheme());
        m_nav_stack.push(std::make_shared<MainScreen>(std::weak_ptr(shared_from_this())));
        auto last = Window::getTime();
        m_renderer.load();
        m_nav_stack.top()->onInit();
        while (!m_window.isClosed()) {
            const auto now = Window::getTime();
            m_nav_stack.top()->onUpdate(static_cast<float>(now - last) / 1000.f);
            last = now;

            Event e{};
            while (Window::poll(e)) {
                if (e.type == EventType::WindowClose) {
                    m_window.close();
                }
                if (e.type == EventType::WindowResize) {
                    m_view = glm::ivec2(e.window.width, e.window.height);
                    m_renderer.resize(m_view);
                }
                m_nav_stack.top()->onEvent(e);
            }

            m_renderer.begin();
            m_nav_stack.top()->onDraw(m_renderer);
            m_renderer.end();

            m_window.swap();
        }
        m_nav_stack.top()->onDeinit();
        m_renderer.unload();
        return 0;
    }

}
