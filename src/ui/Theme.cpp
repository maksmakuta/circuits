#include "Theme.h"

namespace circuits {

    ThemePtr getTheme(const bool is_dark) {
        if (is_dark) {
            return std::make_shared<Theme>(
                Color(0xFF121212),
                Color(0xFF1F6FEB),
                Color(0xFFE0E0E0)
            );
        }
        return std::make_shared<Theme>(
            Color(0xFFFFFFFF),
            Color(0xFF0066CC),
            Color(0xFF000000)
        );
    }

}
