#ifndef CIRCUITS_SWITCH_H
#define CIRCUITS_SWITCH_H

#include "core/IWidget.h"

namespace circuits {

    class Toggle final : public IWidget{
    public:
        explicit Toggle(bool state = true);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;
        void onEvent(const Event &e) override;
    private:
        bool m_switch;
    };

}

#endif //CIRCUITS_SWITCH_H