#include "MainScreen.h"

#include "ui/UI.h"

namespace circuits {

    MainScreen::MainScreen() {
        m_list = column({
            label("Hello"),
            label("World"),
            button(
            column({
                    label("Click"),
                    label("Me"),
                })
            )
        });
    }

    void MainScreen::onInit() {
        m_list->setContext(getContext());
        const auto size = m_list->onMeasure({});
        const auto view_rect = Rect({},m_view);
        m_list->onLayout(Rect({},size).centeredIn(view_rect));
    }

    void MainScreen::onDeinit() {}

    void MainScreen::onDraw(Renderer& r) {
        clear(getContext()->getTheme()->background);
        m_list->onDraw(r);
    }

    void MainScreen::onUpdate(float dt){ }

    void MainScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_view = glm::ivec2(e.window.width, e.window.height);
        }
        m_list->onEvent(e);
    }

}
