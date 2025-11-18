#include "MainScreen.h"

#include <SDL3/SDL_keycode.h>

namespace circuits {

    void MainScreen::onInit() { }

    void MainScreen::onDeinit() { }

    void MainScreen::onDraw(Renderer& r) {
        clear(0xFF202020);
    }

    void MainScreen::onUpdate(float dt){ }

    void MainScreen::onEvent(const Event& e){ }

}
