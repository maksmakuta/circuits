#include "Button.h"

#include <utility>
#include <SDL3/SDL_mouse.h>

#include "utils/ColorUtils.h"
#include "utils/WidgetUtils.h"

namespace circuits {

    Button::Button(WidgetPtr p, ButtonCallback c) : m_inner(std::move(p)), m_callback(std::move(c)) {
        setAppearance(Appearance::Primary);
    }

    glm::ivec2 Button::onMeasure(const glm::ivec2 &max) {
        auto size = glm::ivec2(0);

        if(m_inner != nullptr) {
            const auto& child = m_inner;
            const auto child_size = WidgetUtils::preferredSize(
                child->getModifier().getParams(),
                WidgetUtils::sizeWithPadding(child, max),
                max
            );
            m_child_size = child_size;
            size = glm::max(size, child_size);
        }else {
            size += glm::ivec2{50,30};
        }

        return size;
    }

    void Button::onLayout(const Rect& r) {
        IWidget::onLayout(r);

        if(m_inner == nullptr) return;

        const auto offset = getRect().pos;
        const auto& child = m_inner;
        const auto mod = child->getModifier();
        const auto& child_size = m_child_size;
        const auto g_offset = WidgetUtils::applyGravity(
            mod.getGravity(),
            child_size,
            getRect().size
        );
        const auto rect = Rect(offset + g_offset, child_size);
        child->onLayout(WidgetUtils::removePadding(rect,mod.getPadding()));

    }

    void Button::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto& [pos, size] = getRect();
        r.rect(pos,size,theme.shape.cornerMedium);
        r.fill(ColorUtils::resolveColor(getAppearance(),state()));

        if (m_inner) {
            m_inner->onDraw(r);
        }
    }

    void Button::onUpdate(const float dt) {
        if (m_inner) {
            m_inner->onUpdate(dt);
        }
    }

    void Button::onButtonEvent(const Event& event) {
        if (state() == State::Disabled)
            return;

        const Rect rect = getRect();
        const glm::ivec2 mousePos = event.type == EventType::MouseMove
            ? glm::ivec2{event.mouseMove.x, event.mouseMove.y}
        : glm::ivec2{event.mouseButton.x, event.mouseButton.y};

        const bool inside = rect.contains(mousePos);

        switch (event.type) {

            case EventType::MouseMove: {
                if (inside) {
                    if (state() != State::Pressed && state() != State::Hovered)
                        setState(State::Hovered);
                } else {
                    if (state() != State::Enabled)
                        setState(State::Enabled);
                }
            } break;

            case EventType::MouseDown: {
                if (inside && event.mouseButton.button == SDL_BUTTON_LEFT) {
                    if (state() != State::Pressed)
                        setState(State::Pressed);
                }
            } break;

            case EventType::MouseUp: {
                if (state() == State::Pressed) {
                    if (inside) {
                        setState(State::Hovered);
                        if (m_callback)
                            m_callback();
                    } else {
                        setState(State::Enabled);
                    }
                }
            } break;

            default:
                break;
        }
    }

    void Button::onEvent(const Event& e) {
        onButtonEvent(e);

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
