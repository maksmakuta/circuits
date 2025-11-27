#include "UIScreen.h"

#include "IContext.h"

namespace circuits {

    UIScreen::UIScreen(const std::weak_ptr<IContext> &ctx) : IScreen(ctx) {}

    void UIScreen::onInit(){
        m_ui = onUI();
    }

    void UIScreen::onDeinit(){}

    void UIScreen::onDraw(Renderer& r){
        clear(currentTheme().palette.background);
        m_ui->onDraw(r);
    }

    void UIScreen::onUpdate(const float dt){
        if (m_recompose) {
            onResize(m_ui,getContext()->screenSize());
            m_recompose = false;
        }
        m_ui->onUpdate(dt);
    }

    void UIScreen::onEvent(const Event& e){
        if (e.type == EventType::WindowResize) {
            onResize(m_ui,{e.window.width,e.window.height});
        }else if (e.type == EventType::Recompose) {
            m_recompose = true;
        }
        m_ui->onEvent(e);
    }

}
