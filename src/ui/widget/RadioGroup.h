#ifndef CIRCUITS_RADIOGROUP_H
#define CIRCUITS_RADIOGROUP_H

#include "RadioButton.h"
#include "core/IWidget.h"

namespace circuits {

    class RadioGroup final : public IWidget {
    public:
        RadioGroup(const WidgetList& widgets);
        RadioGroup(const std::initializer_list<std::string>& strings);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onLayout(const Rect &r) override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &e) override;
    private:

    };

}

#endif //CIRCUITS_RADIOGROUP_H