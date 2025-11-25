#ifndef CIRCUITS_THEMEMANAGER_H
#define CIRCUITS_THEMEMANAGER_H

#include "../ui/Theme.h"

namespace circuits {

    class ThemeManager {
    public:
        static ThemeManager& instance();

        void setTheme(const Theme& theme);

        const Theme& getTheme() const;
        const ThemeName& getSystemTheme() const;

    private:
        Theme currentTheme;
        ThemeName systemTheme = ThemeName::Unknown;

        ThemeManager();
        ~ThemeManager();
    };

    Theme currentTheme();

}

#endif //CIRCUITS_THEMEMANAGER_H