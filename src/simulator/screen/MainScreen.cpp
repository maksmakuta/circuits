#include "MainScreen.h"

#include "ui/UI.h"

namespace circuits {

    void MainScreen::onInit(){
        const auto end = Modifier().gravity(Gravity::Right);
        const auto fill = Modifier().fillWidth().padding(4,8);
        m_ui = column({
            row({
                label("Option 1"),
                toggle(true, end)
            }, fill),
            row({
                label("Option 2"),
                toggle(true, end)
            }, fill),
        }, Modifier().width(300));

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
        const auto mod = m_ui->getModifier();
        const auto content = m_ui->onMeasure(size);
        const auto view = Rect({},content);
        m_ui->onLayout(mod.applyPadding(view));
    }

    MainVM& MainScreen::viewmodel() {
        return m_viewmodel;
    }

}
