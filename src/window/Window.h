#ifndef CIRCUITS_WINDOW_H
#define CIRCUITS_WINDOW_H

#include <glm/vec2.hpp>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>

#include "Event.h"

namespace circuits {

    class Window {
    public:
        Window();
        Window(const char* title, const glm::ivec2& size);
        ~Window();

        [[nodiscard]] bool isClosed() const;

        [[nodiscard]] const char* getTitle() const;
        [[nodiscard]] glm::ivec2 getPos() const;
        [[nodiscard]] glm::ivec2 getSize() const;
        [[nodiscard]] Cursor getCursor() const;

        void move(const glm::ivec2&) const;
        void resize(const glm::ivec2&) const;
        void setTitle(const char*) const;
        void setCursor(const Cursor&);

        void showCursor(bool) const;
        void enableInput(bool) const;

        void close();
        void swap() const;

        static bool poll(Event&);
        static uint64_t getTime();

    private:
        bool m_running = false;
        Cursor m_cursor = Cursor::Default;
        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;
        SDL_Cursor* m_cursor_ptr = nullptr;
    };

}

#endif //CIRCUITS_WINDOW_H