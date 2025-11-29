#include "RadioButton.h"

namespace circuits {

    RadioButton::RadioButton(RadioGroup *parent) {

    }

    glm::ivec2 RadioButton::onMeasure(const glm::ivec2 &max) {
        return {20,20};
    }

    void RadioButton::onDraw(Renderer& r) {
        const auto theme = currentTheme();
        const auto center = getRect().pos + getRect().size / 2;

        r.rect(getRect().pos, getRect().size);
        r.fill(Color(0xFF00FF00));

        r.circle(center,10);
        r.stroke(theme.palette.outline,2);

        if (isSelected()) {
            r.circle(center,8);
            r.fill(theme.palette.primary);
        }
    }

    void RadioButton::select(const bool v) {
        if (is_selected != v) {
            is_selected = v;
        }
    }

    bool RadioButton::isSelected() const {
        return is_selected;
    }

}