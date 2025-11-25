#ifndef CIRCUITS_CARD_H
#define CIRCUITS_CARD_H

#include "core/IWidget.h"

namespace circuits {

    class Card final : public IWidget, public std::enable_shared_from_this<Card> {
    public:
        explicit Card(WidgetPtr);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onLayout(const Rect &r) override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &e) override;

    private:
        WidgetPtr m_inner;
    };

}

#endif //CIRCUITS_CARD_H