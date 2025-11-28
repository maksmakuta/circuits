#include "Checkbox.h"

#include <SDL3/SDL_mouse.h>

namespace circuits {

    Checkbox::Checkbox(const bool state) : m_value(state) {
        setAppearance(Appearance::Normal);
    }

    Checkbox::Checkbox(Observable<bool>& state) : Checkbox(state.getValue()) {
        state.observe([this](const bool val) {
            setValue(val);
        });
    }

    glm::ivec2 Checkbox::onMeasure(const glm::ivec2 &max) {
        return glm::ivec2(20);
    }

    void Checkbox::onDraw(Renderer& r) {
        const auto theme = currentTheme();

        r.rect(getRect().pos, getRect().size);
        r.stroke(theme.palette.outline,state() == State::Hovered ? 2 : 1);

        if (m_value) {
            r.rect(getRect().pos + 3, getRect().size - 6);
            r.fill(theme.palette.primary);
        }
    }

    void Checkbox::onEvent(const Event &e) {
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

    bool Checkbox::getValue() const {
        return m_value;
    }

    void Checkbox::setValue(const bool state) {
        if (m_value != state) {
            m_value = state;
            recompose();
        }
    }

    void Checkbox::toggle() {
        setValue(!m_value);
    }
}
