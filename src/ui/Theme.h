#ifndef CIRCUITS_THEME_H
#define CIRCUITS_THEME_H

#include <memory>

#include "graphics/Color.h"

namespace circuits {

    struct Theme {
        Color background;
        Color primary;
        Color text;
    };

    using ThemePtr = std::shared_ptr<Theme>;

    ThemePtr getTheme(bool is_dark = false);

}

#endif //CIRCUITS_THEME_H