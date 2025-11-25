#include "Window.h"

#include <iostream>
#include <string>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>

#include "glad/gl.h"

namespace circuits {

    void onError(const std::string& message) {
        std::cerr << message << std::endl;
    }

    void Window::initSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != 1) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        }
    }

    void Window::initGL() {
        if (m_window == nullptr) {
            onError("Cannot initialize OpenGL: Window pointer is null");
            return;
        }
        m_context = SDL_GL_CreateContext(m_window);
        if (m_context == nullptr) {
            onError("Cannot create OpenGL context");
            return;
        }

        if (!SDL_GL_SetSwapInterval(1)) {
            std::fprintf(stderr, "Warning: could not set swap interval: %s\n", SDL_GetError());
        }

        if (!gladLoadGL(SDL_GL_GetProcAddress)) {
            onError("Cannot load GLAD");
            return;
        }

        SDL_GL_MakeCurrent(m_window, m_context);

        m_running = true;
    }

    void Window::deinitSDL() {
        SDL_Quit();
    }

    void Window::deinitGL() const {
        SDL_GL_DestroyContext(m_context);
    }

    Window::Window() : Window("Circuits", {640,480}){}

    Window::Window(const char* title, const glm::ivec2& size) {
        initSDL();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

        m_window = SDL_CreateWindow(title, size.x, size.y, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        initGL();

        glEnable(GL_MULTISAMPLE);
    }

    Window::~Window() {
        deinitGL();
        SDL_DestroyWindow(m_window);
        deinitSDL();
    }

    bool Window::isClosed() const {
        return !m_running;
    }

    const char* Window::getTitle() const {
        return SDL_GetWindowTitle(m_window);
    }

    glm::ivec2 Window::getPos() const {
        glm::ivec2 pos;
        SDL_GetWindowPosition(m_window, &pos.x, &pos.y);
        return pos;
    }

    glm::ivec2 Window::getSize() const {
        glm::ivec2 size;
        SDL_GetWindowSize(m_window, &size.x, &size.y);
        return size;
    }

    void Window::move(const glm::ivec2& pos) const {
        SDL_SetWindowPosition(m_window, pos.x, pos.y);
    }

    void Window::resize(const glm::ivec2& size) const {
        SDL_SetWindowSize(m_window, size.x, size.y);
    }

    void Window::setTitle(const char* title) const {
        SDL_SetWindowTitle(m_window,title);
    }

    void Window::close() {
        m_running = false;
    }

    bool Window::poll(Event& out) {
        SDL_Event e;
        if (!SDL_PollEvent(&e))
            return false;

        const auto mods = Mods{
            .shift = (SDL_GetModState() & SDL_KMOD_SHIFT) != 0,
            .ctrl  = (SDL_GetModState() & SDL_KMOD_CTRL)  != 0,
            .alt   = (SDL_GetModState() & SDL_KMOD_ALT)   != 0,
        };

        switch (e.type) {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                out = Event::WindowClose();
                break;

            case SDL_EVENT_WINDOW_RESIZED:
                out = Event::WindowResize(e.window.data1, e.window.data2);
                break;

            case SDL_EVENT_KEY_DOWN:
                out = Event::KeyDown(e.key.key, e.key.repeat != 0, mods);
                break;

            case SDL_EVENT_KEY_UP:
                out = Event::KeyUp(e.key.key, mods);
                break;

            case SDL_EVENT_MOUSE_MOTION:
                out = Event::MouseMove(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel, mods);
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                out = Event::MouseDown(e.button.button, e.button.x, e.button.y, mods);
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                out = Event::MouseUp(e.button.button, e.button.x, e.button.y, mods);
                break;

            case SDL_EVENT_MOUSE_WHEEL:
                out = Event::MouseWheel(e.wheel.x, e.wheel.y, mods);
                break;

            default:
                return false;
        }

        return true;
    }

    void Window::swap() const {
        SDL_GL_SwapWindow(m_window);
    }

    uint64_t Window::getTime() {
        return SDL_GetTicks();
    }
}
