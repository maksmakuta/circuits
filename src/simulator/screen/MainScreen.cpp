#include "MainScreen.h"

namespace circuits {

    MainScreen::MainScreen() {
        m_list = std::make_unique<Column>(std::initializer_list<WidgetPtr>{
            std::make_shared<Label>("Hello"),
            std::make_shared<Label>("World")
        });
    }

    void MainScreen::onInit() {
        m_list->setContext(getContext());
        const auto size = m_list->onMeasure({});
        m_list->onLayout(m_view / 2 - size / 2, size);
    }

    void MainScreen::onDeinit() {}

    void MainScreen::onDraw(Renderer& r) {
        clear(getContext()->theme->background);
        m_list->onDraw(r);
    }

    void MainScreen::onUpdate(float dt){ }

    void MainScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_view = glm::ivec2(e.window.width, e.window.height);
        }
    }

}
