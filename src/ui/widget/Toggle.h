#ifndef CIRCUITS_SWITCH_H
#define CIRCUITS_SWITCH_H

#include "core/IWidget.h"
#include "rx/Observable.h"

namespace circuits {

    class Toggle final : public IWidget{
    public:
        explicit Toggle(bool state);
        explicit Toggle(Observable<bool>& state);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;
        void onEvent(const Event &e) override;

        void setValue(bool value);
        [[nodiscard]] bool getValue() const;
        void toggle();
    private:
        bool m_switch;
    };

}

#endif //CIRCUITS_SWITCH_H