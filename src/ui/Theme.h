#ifndef CIRCUITS_THEME_H
#define CIRCUITS_THEME_H

#include <memory>

namespace circuits {

    struct Theme { /* ... */ };

    using ThemePtr = std::shared_ptr<Theme>;

    ThemePtr getTheme(bool is_dark = false);

}

#endif //CIRCUITS_THEME_H