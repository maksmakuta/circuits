#ifndef CIRCUITS_BUTTON_H
#define CIRCUITS_BUTTON_H

#include "core/IWidget.h"

namespace circuits {

    class Button final : public IWidget{
    public:
        explicit Button(WidgetPtr = nullptr);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onLayout(const Rect &) override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &) override;
    private:
        WidgetPtr m_inner;
    };

}

#endif //CIRCUITS_BUTTON_H