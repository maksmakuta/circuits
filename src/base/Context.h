#ifndef CIRCUITS_CONTEXT_H
#define CIRCUITS_CONTEXT_H

#include "graphics/Font.h"
#include "ui/Theme.h"

namespace circuits {

    struct Context {
        explicit Context(int font_size = 32);

        void switchTheme();
        void unload();

        const ThemePtr& getTheme() const;
        const Font& getFont() const;
    protected:
        ThemePtr theme;
        Font font;
        bool is_dark{false};
    };

    using ContextPtr = std::shared_ptr<Context>;

}

#endif //CIRCUITS_CONTEXT_H