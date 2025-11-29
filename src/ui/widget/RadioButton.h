#ifndef CIRCUITS_RADIOBUTTON_H
#define CIRCUITS_RADIOBUTTON_H

#include "core/IWidget.h"

namespace circuits {

    class RadioGroup;
    class RadioButton;

    using OnCheckedListener = std::function<void(RadioButton*)>;

    class RadioButton final : public IWidget {
    public:
        friend class RadioGroup;

        explicit RadioButton(RadioGroup* parent = nullptr);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;

        void select(bool);
        [[nodiscard]] bool isSelected() const;

    private:
        bool is_selected = false;
    };

}

#endif //CIRCUITS_RADIOBUTTON_H