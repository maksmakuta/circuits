#include "Label.h"

#include "manager/ThemeManager.h"

namespace circuits {

    Color onText(const Appearance text_appearance) {
        switch (text_appearance) {
            case Appearance::Surface:
                return currentTheme().palette.onSurface;
            case Appearance::SurfaceVariant:
                return currentTheme().palette.onSurfaceVariant;
            case Appearance::Primary:
                return currentTheme().palette.onPrimary;
            case Appearance::Secondary:
                return currentTheme().palette.onSecondary;
            case Appearance::Error:
                return currentTheme().palette.onError;
            default:
                return currentTheme().palette.onBackground;
        }
    }

    Font getFont(const FontRole r) {
        switch (r) {
            case FontRole::Title:
                return currentTheme().typography.title;
            case FontRole::Body:
                return currentTheme().typography.body;
            default:
                return currentTheme().typography.label;
        }
    }

    Label::Label(std::string text, const FontRole r) : m_text(std::move(text)), m_role(r) {}

    glm::ivec2 Label::onMeasure(const glm::ivec2 &max){
        const auto font = getFont(m_role);
        return font.textSize(m_text);
    }

    void Label::onDraw(Renderer& r){
        const auto theme = currentTheme();
        r.setBaseline(Baseline::Bottom);
        r.text(
            getFont(m_role),
            m_text,
            getRect().pos,
            onText(getParent() ? getParent()->getAppearance() : getAppearance())
        );
    }

}
