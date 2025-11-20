#include "Context.h"

namespace circuits {

    Context::Context(const bool is_dark_theme, const int font_size) {
        theme = getTheme(is_dark_theme);
        font.loadDefault(font_size);
    }

    void Context::unload() {
        font.unload();
    }

}
