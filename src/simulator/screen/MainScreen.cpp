#include "MainScreen.h"

namespace circuits {

    MainScreen::MainScreen() {
        m_text = std::make_unique<Label>("Hello World");
    }

    void MainScreen::onInit() {
        m_text->setContext(getContext());
        const auto size = m_text->onMeasure({});
        m_text->onLayout(m_view / 2 - size / 2, size);
    }

    void MainScreen::onDeinit() {}

    void MainScreen::onDraw(Renderer& r) {
        clear(getContext()->theme->background);
        m_text->onDraw(r);
    }

    void MainScreen::onUpdate(float dt){ }

    void MainScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_view = glm::ivec2(e.window.width, e.window.height);
            onInit();
        }
    }

}
