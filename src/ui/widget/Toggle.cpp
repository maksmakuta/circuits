#include "Toggle.h"

#include <SDL3/SDL_mouse.h>

namespace circuits {

    Toggle::Toggle(const bool state) : m_switch(state) {}

    Toggle::Toggle(Observable<bool>& state) : Toggle(state.getValue()) {
        state.observe([this](const bool val) {
            setValue(val);
        });
    }

    glm::ivec2 Toggle::onMeasure(const glm::ivec2 &max) {
        return glm::ivec2{52,32};
    }

    void Toggle::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto rect = getRect();
        const auto radius = static_cast<float>(rect.size.y >> 1);

        r.rect(rect.pos,rect.size,radius);
        r.fill(m_switch ? theme.palette.primary : theme.palette.background);
        if (!m_switch) {
            r.stroke(theme.palette.outline,theme.shape.borderThickness);
        }

        const int thumb_size = m_switch ? 12 : 8;
        const auto offset = m_switch
            ? glm::ivec2{getRect().size.x - 16, getRect().size.y / 2}
            : glm::ivec2{16, getRect().size.y / 2};
        const auto thumb_pos = rect.pos + offset;
        r.circle(thumb_pos,thumb_size);
        r.fill(m_switch ? theme.palette.background : theme.palette.outline);
    }

    void Toggle::onEvent(const Event &e) {
        if (state() == State::Disabled)
            return;

        const Rect rect = getRect();
        const glm::ivec2 mousePos = e.type == EventType::MouseMove
            ? glm::ivec2{e.mouseMove.x, e.mouseMove.y}
        : glm::ivec2{e.mouseButton.x, e.mouseButton.y};

        const bool inside = rect.contains(mousePos);

        switch (e.type) {

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
                if (inside && e.mouseButton.button == SDL_BUTTON_LEFT) {
                    if (state() != State::Pressed)
                        setState(State::Pressed);
                }
            } break;

            case EventType::MouseUp: {
                if (state() == State::Pressed) {
                    if (inside) {
                        setState(State::Hovered);
                        toggle();
                    } else {
                        setState(State::Enabled);
                    }
                }
            } break;

            default:
                break;
        }
    }

    void Toggle::setValue(const bool value) {
        m_switch = value;
    }

    bool Toggle::getValue() const {
        return m_switch;
    }

    void Toggle::toggle() {
        setValue(!m_switch);
    }

}
