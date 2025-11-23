#ifndef CIRCUITS_THEMEMANAGER_H
#define CIRCUITS_THEMEMANAGER_H

#include "Theme.h"

namespace circuits {

    class ThemeManager {
    public:
        static Theme& current();
        static void setTheme(const Theme& t);
        static void change();

        static Theme getDarkTheme();
        static Theme getLightTheme();
        static SystemTheme getSystemTheme();

    private:
        ThemeManager();
        ~ThemeManager();

        static ThemeManager& instance();

        SystemTheme currentTheme = SystemTheme::Unknown;
        Theme m_theme;
    };

}

#endif //CIRCUITS_THEMEMANAGER_H