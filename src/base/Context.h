#ifndef CIRCUITS_CONTEXT_H
#define CIRCUITS_CONTEXT_H

#include "graphics/Font.h"
#include "ui/Theme.h"

namespace circuits {

    struct Context {
        ThemePtr theme;
        Font font;

        explicit Context(bool is_dark_theme = false, int font_size = 32);

        void unload();
    };

    using ContextPtr = std::shared_ptr<Context>;

}

#endif //CIRCUITS_CONTEXT_H