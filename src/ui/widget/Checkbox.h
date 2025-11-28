#ifndef CIRCUITS_CHECK_H
#define CIRCUITS_CHECK_H

#include "core/IWidget.h"
#include "rx/Observable.h"

namespace circuits {

    class Checkbox final : public IWidget{
    public:
        explicit Checkbox(bool state = false);
        explicit Checkbox(Observable<bool>& state);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;
        void onEvent(const Event &e) override;

        bool getValue() const;
        void setValue(bool state);
        void toggle();

    private:
        bool m_value;
    };

}



#endif //CIRCUITS_CHECK_H