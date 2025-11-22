#include "Context.h"

namespace circuits {

    Context::Context(const int font_size) {
        font.loadDefault(font_size);
        theme = getSystemTheme(&is_dark);
    }

    void Context::switchTheme() {
        is_dark = !is_dark;
        theme = circuits::getTheme(is_dark);
    }

    void Context::unload() {
        font.unload();
    }

    const ThemePtr& Context::getTheme() const {
        return theme;
    }

    const Font& Context::getFont() const {
        return font;
    }
}
