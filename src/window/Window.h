#ifndef CIRCUITS_WINDOW_H
#define CIRCUITS_WINDOW_H

namespace circuits {

    class Window {
    public:
        Window();
        ~Window();

        bool isClosed() const;

        glm::ivec2 getPos() const;
        glm::ivec2 getSize() const;

        void move(const glm::ivec2&);
        void resize(const glm::ivec2&);

        void poll();
        void swap();

    private:
        SDL_Window* m_window = nullptr;
    };

}

#endif //CIRCUITS_WINDOW_H