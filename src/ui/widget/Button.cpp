#include "Button.h"

#include <utility>
#include <SDL3/SDL_mouse.h>

namespace circuits {

    Button::Button(WidgetPtr p, ButtonCallback c) : m_inner(std::move(p)), m_callback(std::move(c)) {
        setAppearance(Appearance::Primary);
    }

    glm::ivec2 Button::onMeasure(const glm::ivec2 &max) {
        if (!m_inner)
            return glm::ivec2{10, 10};

        m_inner->setParent(shared_from_this());

        const auto mod = m_inner->getModifier();
        const auto padding = mod.getPadding();

        const glm::ivec2 innerMax = {
            max.x - padding.left - padding.right,
            max.y - padding.top  - padding.bottom
        };

        glm::ivec2 measured = m_inner->onMeasure(innerMax);
        measured = mod.applySize(measured, innerMax);
        measured = mod.applyPadding(measured);

        m_child_size = measured;

        return getModifier().applySize(measured, max);
    }

    void Button::onLayout(const Rect& r) {
        IWidget::onLayout(r);

        if (!m_inner) return;

        const auto& child = m_inner;
        const auto mod = child->getModifier();
        const auto padding = mod.getPadding();
        const auto gravity = mod.getGravity();

        auto size = m_child_size;

        if (mod.getParams().width.unit == SizeUnit::Fill) {
            size.x = getRect().size.x;
        }
        if (mod.getParams().height.unit == SizeUnit::Fill) {
            size.y = getRect().size.y;
        }

        glm::ivec2 finalPos = {
            r.pos.x + padding.left,
            r.pos.y + padding.top
        };

        glm::ivec2 finalSize = size;

        const int freeX = r.size.x - size.x;
        const int freeY = r.size.y - size.y;

        if (any(gravity, Gravity::HCenter))
            finalPos.x = r.pos.x + freeX / 2 + padding.left;
        else if (any(gravity, Gravity::Right))
            finalPos.x = r.pos.x + freeX + padding.left;

        if (any(gravity, Gravity::VCenter))
            finalPos.y = r.pos.y + freeY / 2 + padding.top;
        else if (any(gravity, Gravity::Bottom))
            finalPos.y = r.pos.y + freeY + padding.top;

        child->onLayout({finalPos, finalSize});
    }

    void Button::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto& [pos, size] = getRect();
        r.rect(pos,size,theme.shape.cornerMedium);

        if (state() == State::Hover) {
            const auto col = theme.palette.primary.asVec3() - 0.1f;
            r.fill(Color(col));
        }else if (state() == State::Active) {
            r.fill(theme.palette.secondary);
        } else {
            r.fill(theme.palette.primary);
        }
        if (m_inner) {
            m_inner->onDraw(r);
        }
    }

    void Button::onUpdate(const float dt) {
        if (m_inner) {
            m_inner->onUpdate(dt);
        }
    }

    void Button::onEvent(const Event& e) {
        if (e.type == EventType::MouseDown) {
            const auto pos = glm::ivec2(e.mouseButton.x, e.mouseButton.y);
            if (e.mouseButton.button == SDL_BUTTON_LEFT && getRect().contains(pos) && m_callback) {
                m_callback();
            }
        }

        if (m_inner) {
            m_inner->onEvent(e);
        }
    }

    void Button::setInnerWidget(WidgetPtr widget) {
        m_inner = std::move(widget);
    }

    void Button::setCallback(ButtonCallback callback) {
        m_callback = std::move(callback);
    }

    WidgetPtr Button::getInnerWidget() const {
        return m_inner;
    }

    ButtonCallback Button::getCallback() const {
        return m_callback;
    }

}
