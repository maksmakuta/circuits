#ifndef CIRCUITS_BUTTON_H
#define CIRCUITS_BUTTON_H

#include "core/IWidget.h"

namespace circuits {

    using ButtonCallback = std::function<void()>;

    class Button final : public IWidget, public std::enable_shared_from_this<Button>{
    public:
        explicit Button(WidgetPtr = nullptr, ButtonCallback = ButtonCallback{});

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onLayout(const Rect &) override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &) override;

        void setInnerWidget(WidgetPtr widget);
        void setCallback(ButtonCallback callback);

        WidgetPtr getInnerWidget() const;
        ButtonCallback getCallback() const;

    private:
        void onButtonEvent(const Event & event);

        glm::ivec2 m_child_size{0};
        WidgetPtr m_inner;
        ButtonCallback m_callback;
    };

}

#endif //CIRCUITS_BUTTON_H