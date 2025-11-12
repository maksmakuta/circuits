#include "glad/gl.h"
#include "window/Window.h"

int main() {
    auto window = circuits::Window();
    while (!window.isClosed()) {
        window.poll();
        glClearColor(0,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        window.swap();
    }
    return 0;
}
