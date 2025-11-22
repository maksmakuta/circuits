#ifndef CIRCUITS_BUTTON_H
#define CIRCUITS_BUTTON_H

#include "base/interface/IWidget.h"

namespace circuits {

    using ButtonCallback = std::function<void()>;

    class Button final : public IWidget{
    public:
        explicit Button(WidgetPtr  inner, ButtonCallback  callback = {}, const Modifier& m = {});

        glm::ivec2 onMeasure(const glm::ivec2 &max_size) override;
        void onLayout(const Rect &r) override;
        void onDraw(Renderer &) override;
        void onEvent(const Event &) override;
    private:
        WidgetPtr m_inner;
        ButtonCallback m_callback;
        bool is_hovered = false;
    };

}

#endif //CIRCUITS_BUTTON_H