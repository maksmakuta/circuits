#include "Label.h"

#include "utils/ColorUtils.h"
#include "utils/WidgetUtils.h"

namespace circuits {

    Label::Label(Observable<std::string>& val, const FontRole role) : Label(val.getValue(),role){
        val.observe([this](const std::string& v) {
            setText(v);
        });
    }

    Label::Label(std::string text, const FontRole r) : m_text(std::move(text)), m_role(r) {}

    glm::ivec2 Label::onMeasure(const glm::ivec2 &max){
        return WidgetUtils::getFont(m_role).textSize(m_text);
    }

    void Label::onDraw(Renderer& r){
        const auto theme = currentTheme();
        r.text(
            WidgetUtils::getFont(m_role),
            m_text,
            getRect().pos,
            ColorUtils::getBaseOnColor(getParent() ? getParent()->getAppearance() : getAppearance())
        );
    }

    void Label::setText(std::string text) {
        if (m_text != text) {
            m_text = std::move(text);
            recompose();
        }
    }

    void Label::setFontRole(const FontRole value) {
        m_role = value;
    }

    std::string Label::getText() const {
        return m_text;
    }

    FontRole Label::getFontRole() const {
        return m_role;
    }

}
