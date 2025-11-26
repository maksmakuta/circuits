#ifndef CIRCUITS_IWIDGET_H
#define CIRCUITS_IWIDGET_H

#include <memory>
#include <utility>

#include "Rect.h"
#include "Modifier.h"

#include "graphics/Renderer.h"
#include "enums/Appearance.h"
#include "enums/State.h"
#include "window/Event.h"

namespace circuits {

    class IWidget;

    using WidgetPtr = std::shared_ptr<IWidget>;
    using WidgetList = std::initializer_list<WidgetPtr>;

    class IWidget {
    public:
        explicit IWidget(WidgetPtr parent = nullptr) : m_parent(std::move(parent)) {}
        virtual ~IWidget() = default;

        virtual glm::ivec2 onMeasure(const glm::ivec2& max) = 0;
        virtual void onLayout(const Rect& r) {
            setRect(r);
        }
        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float){}

        virtual void onEvent(const Event& e) {}

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

        void setAppearance(const Appearance a) {
            m_appearance = a;
        }

        void setParent(const WidgetPtr& p) {
            m_parent = p;
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

        [[nodiscard]] Appearance getAppearance() const {
            return m_appearance;
        }

        [[nodiscard]] WidgetPtr getParent() const {
            return m_parent;
        }

    private:
        Rect m_rect;
        WidgetPtr m_parent;
        Modifier m_modifier;
        State m_state = State::Normal;
        Appearance m_appearance = Appearance::Normal;
    };

}

#endif //CIRCUITS_IWIDGET_H