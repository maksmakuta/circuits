#ifndef CIRCUITS_THEMEMANAGER_H
#define CIRCUITS_THEMEMANAGER_H

#include "Theme.h"

namespace circuits {

    class ThemeManager {
    public:
        static ThemeManager& instance() {
            static ThemeManager _instance;
            return _instance;
        }

        void setTheme(const Theme& theme) {
            currentTheme = theme;
            systemTheme = theme.theme;
        }

        const Theme& getTheme() const {
            return currentTheme;
        }

        const SystemTheme& getSystemTheme() const {
            return systemTheme;
        }

    private:
        Theme currentTheme;
        SystemTheme systemTheme = SystemTheme::Unknown;

        ThemeManager() {
            setTheme(Theme::getTheme());
        }

        ~ThemeManager() {
            currentTheme.typography.label.unload();
            currentTheme.typography.body.unload();
            currentTheme.typography.title.unload();
        }

    };

    inline Theme currentTheme() {
        return ThemeManager::instance().getTheme();
    }

}

#endif //CIRCUITS_THEMEMANAGER_H