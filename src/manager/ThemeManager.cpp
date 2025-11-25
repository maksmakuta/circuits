#include "ThemeManager.h"

namespace circuits {

    ThemeManager& ThemeManager::instance() {
        static ThemeManager _instance;
        return _instance;
    }

    void ThemeManager::setTheme(const Theme& theme) {
        currentTheme = theme;
        systemTheme = theme.theme;
    }

    const Theme& ThemeManager::getTheme() const {
        return currentTheme;
    }

    const ThemeName& ThemeManager::getSystemTheme() const {
        return systemTheme;
    }

    ThemeManager::ThemeManager() {
        setTheme(Theme::getTheme());
    }

    ThemeManager::~ThemeManager() {
        currentTheme.typography.label.unload();
        currentTheme.typography.body.unload();
        currentTheme.typography.title.unload();
    }

    Theme currentTheme() {
        return ThemeManager::instance().getTheme();
    }

}