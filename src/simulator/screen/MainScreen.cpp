#include "MainScreen.h"

#include <iostream>

#include "ui/UI.h"

namespace circuits {

    MainScreen::MainScreen() {}

    void MainScreen::onInit() {

    }

    void MainScreen::onDeinit() {}

    void MainScreen::onDraw(Renderer& r) {
        clear(getContext()->getTheme()->background);
    }

    void MainScreen::onUpdate(float dt){ }

    void MainScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_view = glm::ivec2(e.window.width, e.window.height);
        }
    }

}
