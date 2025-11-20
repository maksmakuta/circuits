#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit() {}

    void MainScreen::onDeinit() {}

    void MainScreen::onDraw(Renderer& r) {
        clear(getContext()->theme->background);
    }

    void MainScreen::onUpdate(float dt){ }

    void MainScreen::onEvent(const Event& e) {}

}
