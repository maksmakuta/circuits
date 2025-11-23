#include "MainScreen.h"

#include "ui/theme/ThemeManager.h"

namespace circuits {

    void MainScreen::onInit(){
        m_label = std::make_shared<Label>("Hello, world!");
    }

    void MainScreen::onDeinit(){

    }

    void MainScreen::onDraw(Renderer& r){
        clear(ThemeManager::current().palette.background);

        m_label->onDraw(r);
    }

    void MainScreen::onUpdate(const float dt){
        m_label->onUpdate(dt);
    }

    void MainScreen::onEvent(const Event& e){
        if (e.type == EventType::WindowResize) {
            onResize({e.window.width, e.window.height});
        }
        m_label->onEvent(e);
    }

    void MainScreen::onResize(const glm::ivec2& size) const {
        const auto content = m_label->onMeasure(size);
        const auto view = Rect(size / 2 - content / 2,content);
        m_label->onLayout(view);
    }

    MainVM& MainScreen::viewmodel() {
        return m_viewmodel;
    }
}
