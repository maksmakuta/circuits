#include "MainScreen.h"

#include <SDL3/SDL_keycode.h>

#include "manager/ThemeManager.h"
#include "ui/UI.h"

namespace circuits {

    void MainScreen::onInit(){
        const auto pad8 = Modifier().padding(8);
        m_ui = card(
            column({
                label("Just text", FontRole::Label,pad8),
                button("This is button",pad8),
                input("This is a Input", pad8),
                toggle(true,pad8)
            })
        );
    }

    void MainScreen::onDeinit(){}

    void MainScreen::onDraw(Renderer& r){
        clear(currentTheme().palette.background);
        m_ui->onDraw(r);
    }

    void MainScreen::onUpdate(const float dt){
        m_ui->onUpdate(dt);
    }

    void MainScreen::onEvent(const Event& e){
        m_ui->onEvent(e);
        if (e.type == EventType::WindowResize) {
            onResize({e.window.width, e.window.height});
        }
    }

    void MainScreen::onResize(const glm::ivec2& size) const {
        const auto mod = m_ui->getModifier();
        const auto content = m_ui->onMeasure(size);
        const auto view = Rect(size / 2 - content / 2,content);
        m_ui->onLayout(mod.applyPadding(view));
    }

    MainVM& MainScreen::viewmodel() {
        return m_viewmodel;
    }

}
