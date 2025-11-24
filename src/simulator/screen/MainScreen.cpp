#include "MainScreen.h"

#include "ui/UI.h"

namespace circuits {

    void MainScreen::onInit(){
        m_ui = button("Click me");
    }

    void MainScreen::onDeinit(){

    }

    void MainScreen::onDraw(Renderer& r){
        clear(currentTheme().palette.background);

        m_ui->onDraw(r);
    }

    void MainScreen::onUpdate(const float dt){
        m_ui->onUpdate(dt);
    }

    void MainScreen::onEvent(const Event& e){
        if (e.type == EventType::WindowResize) {
            onResize({e.window.width, e.window.height});
        }
        m_ui->onEvent(e);
    }

    void MainScreen::onResize(const glm::ivec2& size) const {
        const auto content = m_ui->onMeasure(size);
        const auto view = Rect(size / 2 - content / 2,content);
        m_ui->onLayout(view);
    }

    MainVM& MainScreen::viewmodel() {
        return m_viewmodel;
    }

}
