#include "UIScreen.h"
#include "IContext.h"

#include "utils/WidgetUtils.h"

namespace circuits {

    UIScreen::UIScreen(const std::weak_ptr<IContext> &ctx) : IScreen(ctx) {}

    void UIScreen::onInit(){
        m_ui = onUI();
    }

    void UIScreen::onResize(const WidgetPtr& widget, const glm::ivec2& v_size) {
        if (!widget) return;

        const auto mod = widget->getModifier();

        const auto child_size = WidgetUtils::preferredSize(
              mod.getParams(),
              WidgetUtils::sizeWithPadding(widget, v_size),
              v_size);

        const auto g_offset = WidgetUtils::applyGravity(
            mod.getGravity(),
            child_size,
            v_size
        );

        const auto rect = Rect(g_offset, child_size);
        widget->onLayout(WidgetUtils::removePadding(rect,mod.getPadding()));
    }

    void UIScreen::onDeinit(){}

    void UIScreen::onDraw(Renderer& r){
        if (m_recompose) {
            onResize(m_ui,getContext()->screenSize());
            m_recompose = false;
        }

        clear(currentTheme().palette.background);
        m_ui->onDraw(r);
    }

    void UIScreen::onUpdate(const float dt){
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
