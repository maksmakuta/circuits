#ifndef CIRCUITS_IWIDGET_H
#define CIRCUITS_IWIDGET_H

#include <memory>
#include <glm/gtc/constants.hpp>

#include "Rect.h"

#include "graphics/Renderer.h"
#include "Modifier.h"
#include "enums/State.h"
#include "ui/theme/ThemeManager.h"
#include "window/Event.h"

namespace circuits {

    class IWidget {
    public:
        virtual ~IWidget() = default;

        virtual glm::ivec2 onMeasure(const glm::ivec2& max) = 0;
        virtual void onLayout(const Rect& r) {
            setRect(r);
        }
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float){}

        virtual void onEvent(const Event& e) {
            if (state() == State::Disable)
                return;

            switch (e.type) {
                case EventType::MouseMove: {
                    const glm::vec2 mouse{e.mouseMove.x, e.mouseMove.y};
                    const bool inside = getRect().contains(mouse);

                    if (state() == State::Active) {
                        return;
                    }

                    if (inside)
                        setState(State::Hover);
                    else
                        setState(State::Normal);
                    break;
                }

                case EventType::MouseDown: {
                    if (getRect().contains({e.mouseButton.x, e.mouseButton.y})) {
                        setState(State::Active);
                    }
                    break;
                }

                case EventType::MouseUp: {
                    const glm::vec2 mouse{e.mouseButton.x, e.mouseButton.y};
                    const bool inside = getRect().contains(mouse);
                    if (state() == State::Active) {
                        setState(inside ? State::Hover : State::Normal);
                    }
                    break;
                }

                default:
                    break;
            }
        }


        void setModifier(const Modifier& m) {
            m_modifier = m;
        }

        void setRect(const Rect& r) {
            m_rect = r;
        }

        void setState(const State s) {
            if (m_state == s) return;
            m_state = s;
        }

        [[nodiscard]] Modifier getModifier() const {
            return m_modifier;
        }

        [[nodiscard]] Rect getRect() const {
            return m_rect;
        }

        [[nodiscard]] State state() const {
            return m_state;
        }

    private:
        Rect m_rect;
        Modifier m_modifier;
        State m_state = State::Normal;
    };

    using WidgetPtr = std::shared_ptr<IWidget>;
    using WidgetList = std::initializer_list<WidgetPtr>;

    static Theme currentTheme() {
        return ThemeManager::current();
    }

}

#endif //CIRCUITS_IWIDGET_H