#include "UIScreen.h"

#include "IContext.h"

namespace circuits {

    UIScreen::UIScreen(const std::weak_ptr<IContext> &ctx) : IScreen(ctx) {}

    void UIScreen::onInit(){
        m_ui = onUI();
    }

    void UIScreen::onResize(const WidgetPtr& widget, const glm::ivec2& v_size) {
        if (!widget) return;

        const auto rect = Rect({}, v_size);
        const auto mod = widget->getModifier();
        const auto padding = mod.getPadding();
        const auto gravity = mod.getGravity();

        auto size = widget->onMeasure(v_size);

        if (mod.getParams().width.unit == SizeUnit::Fill) {
            size.x = rect.size.x;
        }
        if (mod.getParams().height.unit == SizeUnit::Fill) {
            size.y = rect.size.y;
        }

        glm::ivec2 finalPos = {
            rect.pos.x + padding.left,
            rect.pos.y + padding.top
        };

        glm::ivec2 finalSize = size;

        const int freeX = rect.size.x - size.x;
        const int freeY = rect.size.y - size.y;

        if (any(gravity, Gravity::HCenter))
            finalPos.x = rect.pos.x + freeX / 2 + padding.left;
        else if (any(gravity, Gravity::Right))
            finalPos.x = rect.pos.x + freeX + padding.left;

        if (any(gravity, Gravity::VCenter))
            finalPos.y = rect.pos.y + freeY / 2 + padding.top;
        else if (any(gravity, Gravity::Bottom))
            finalPos.y = rect.pos.y + freeY + padding.top;

        widget->onLayout({finalPos, finalSize});
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
