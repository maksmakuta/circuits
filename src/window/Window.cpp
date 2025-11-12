#include "Window.h"

#include <iostream>
#include <string>
#include <SDL3/SDL_init.h>

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
        if (!gladLoadGL(SDL_GL_GetProcAddress)) {
            onError("Cannot load GLAD");
            return;
        }

        SDL_GL_MakeCurrent(m_window, m_context);

        m_running = true;
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    }

    void Window::deinitSDL() {
        SDL_Quit();
    }

    void Window::deinitGL() const {
        SDL_GL_DestroyContext(m_context);
    }

    Window::Window(){
        initSDL();
        m_window = SDL_CreateWindow("Circuits", 800, 600, SDL_WINDOW_OPENGL);
        initGL();
    }

    Window::~Window() {
        deinitGL();
        SDL_DestroyWindow(m_window);
        deinitSDL();
    }

    bool Window::isClosed() const {
        return !m_running;
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

    void Window::close() {
        m_running = false;
    }

    void Window::poll() {
        //SDL_PollEvent();
    }

    void Window::swap() {
        SDL_GL_SwapWindow(m_window);
    }

}
