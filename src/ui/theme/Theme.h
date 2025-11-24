#ifndef CIRCUITS_THEME_H
#define CIRCUITS_THEME_H

#include "enums/SystemTheme.h"
#include "graphics/Color.h"
#include "graphics/Font.h"

namespace circuits {

    struct Palette {
        Color background;
        Color primary;
        Color surface;
        Color border;
        Color text;
    };

    struct Style {
        float cornerRadius{0};
        float borderRadius{0};
        float borderThickness{0};
    };

    struct Theme {
        Palette palette;
        Style style;
        Font font;
        SystemTheme theme = SystemTheme::Unknown;
    };

}


#endif //CIRCUITS_THEME_H