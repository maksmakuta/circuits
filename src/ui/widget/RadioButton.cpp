#include "RadioButton.h"

#include <SDL3/SDL_mouse.h>

namespace circuits {

    RadioButton::RadioButton(RadioGroup *parent) {

    }

    glm::ivec2 RadioButton::onMeasure(const glm::ivec2 &max) {
        return {20,20};
    }

    void RadioButton::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto center = getRect().pos + getRect().size / 2;

        r.circle(center,10);
        r.stroke(theme.palette.outline,state() == State::Hovered ? 2 : 1);

        if (isSelected()) {
            r.circle(center,8);
            r.fill(theme.palette.primary);
        }
    }

    void RadioButton::onEvent(const Event &e) {
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
                        //TODO(select radiobutton)
                    } else {
                        setState(State::Enabled);
                    }
                }
            } break;

            default:
                break;
        }
    }

    void RadioButton::select(const bool v) {
        if (is_selected != v) {
            is_selected = v;
        }
    }

    bool RadioButton::isSelected() const {
        return is_selected;
    }

}
