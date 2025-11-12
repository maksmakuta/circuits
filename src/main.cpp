#include "glad/gl.h"
#include "window/Window.h"

int main() {
    auto window = circuits::Window();
    while (!window.isClosed()) {
        circuits::Event e;
        while(circuits::Window::poll(e)) {
            if (e.type == circuits::EventType::WindowClose) {
                window.close();
            }
        }
        glClearColor(0.1,0.1,0.1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        window.swap();
    }
    return 0;
}
