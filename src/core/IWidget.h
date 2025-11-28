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
        explicit IWidget(const WidgetPtr& parent = nullptr) : m_parent(parent) {}
        virtual ~IWidget() = default;

        virtual glm::ivec2 onMeasure(const glm::ivec2& max) = 0;
        virtual void onLayout(const Rect& r) {
            setRect(r);
        }

        virtual void onDraw(Renderer&) = 0;
        virtual void onUpdate(float){}
        virtual void onEvent(const Event& e) {}

        void setModifier(const Modifier&);
        void setRect(const Rect&);
        void setState(State);
        void setAppearance(Appearance);
        void setParent(const WidgetPtr&);

        static void recompose();

        [[nodiscard]] Modifier getModifier() const;
        [[nodiscard]] Rect getRect() const;
        [[nodiscard]] State state() const;
        [[nodiscard]] Appearance getAppearance() const;
        [[nodiscard]] WidgetPtr getParent() const;

    private:
        Rect m_rect;
        std::weak_ptr<IWidget> m_parent;
        Modifier m_modifier;
        State m_state = State::Enabled;
        Appearance m_appearance = Appearance::Normal;
    };

}

#endif //CIRCUITS_IWIDGET_H