#ifndef CIRCUITS_WINDOW_H
#define CIRCUITS_WINDOW_H

#include <glm/vec2.hpp>
#include <SDL3/SDL_video.h>

#include "Event.h"

namespace circuits {

    class Window {
    public:
        Window();
        ~Window();

        [[nodiscard]] bool isClosed() const;

        [[nodiscard]] glm::ivec2 getPos() const;
        [[nodiscard]] glm::ivec2 getSize() const;

        void move(const glm::ivec2&) const;
        void resize(const glm::ivec2&) const;

        void close();
        static bool poll(Event&);
        void swap();

    private:
        static void initSDL();
        static void deinitSDL();

        void initGL();
        void deinitGL() const;

        bool m_running = false;
        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;
    };

}

#endif //CIRCUITS_WINDOW_H