#include "MainScreen.h"

#include "ui/UI.h"

namespace circuits {

    MainScreen::MainScreen(const std::weak_ptr<IContext> &ctx) : IScreen(ctx) {}

    void MainScreen::onInit(){
        const auto pad8 = Modifier().padding(8);
        const auto pad8c = Modifier().padding(8).height(48).width(48).center();
        m_ui = card(
            column({
                label(
                    viewmodel().counter_str.getValue(),
                    FontRole::Title,
                    Modifier().padding(8).center()
                ),
                row({
                    button(label("-",FontRole::Title,Modifier().center()),pad8c),
                    button(label("+",FontRole::Title,Modifier().center()),pad8c),
                },pad8)
            },pad8)
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
