#include "ThemeManager.h"

#include <SDL3/SDL_video.h>

namespace circuits {

    Theme& ThemeManager::current() {
        return instance().m_theme;
    }

    void ThemeManager::setTheme(const Theme& t) {
        instance().m_theme = t;
        instance().currentTheme = t.theme;
        if (!instance().m_theme.font.getGlyph('A')) {
            instance().m_theme.font.loadDefault(32);
        }
    }

    ThemeManager::ThemeManager() = default;

    ThemeManager::~ThemeManager() {
        m_theme.font.unload();
    }

    ThemeManager& ThemeManager::instance() {
        static ThemeManager inst;
        return inst;
    }

    void ThemeManager::change() {
        if (instance().currentTheme == SystemTheme::Unknown) {
            instance().currentTheme = getSystemTheme();
            if (instance().currentTheme == SystemTheme::Dark) {
                setTheme(getDarkTheme());
            }else {
                setTheme(getLightTheme());
            }
            return;
        }
        if (instance().currentTheme == SystemTheme::Light) {
            instance().currentTheme = SystemTheme::Dark;
            setTheme(getDarkTheme());
        }else {
            instance().currentTheme = SystemTheme::Light;
            setTheme(getLightTheme());
        }
    }

    Theme ThemeManager::getLightTheme() {
        Theme theme;
        theme.palette.background = Color::fromBytes(255, 255, 255, 255);
        theme.palette.surface = Color::fromBytes(33, 150, 243, 255);
        theme.palette.primary = Color::fromBytes(255, 255, 0, 255);
        theme.palette.border = Color::fromBytes(200, 200, 200, 255);
        theme.palette.text = Color::fromBytes(32, 32, 32, 255);

        theme.style.cornerRadius = 4.0f;
        theme.style.borderRadius = 4.0f;
        theme.style.borderThickness = 1.0f;

        theme.theme = SystemTheme::Light;
        return theme;
    }

    Theme ThemeManager::getDarkTheme() {
        Theme theme;
        theme.palette.background = Color::fromBytes(32, 32, 32, 255);
        theme.palette.primary = Color::fromBytes(121, 134, 203, 255);
        theme.palette.surface = Color::fromBytes(48, 48, 48, 255);
        theme.palette.border = Color::fromBytes(80, 80, 80, 255);
        theme.palette.text = Color::fromBytes(220, 220, 220, 255);

        theme.style.cornerRadius = 4.0f;
        theme.style.borderRadius = 4.0f;
        theme.style.borderThickness = 1.0f;

        theme.theme = SystemTheme::Dark;
        return theme;
    }

    SystemTheme ThemeManager::getSystemTheme() {
        switch (SDL_GetSystemTheme()) {
            case SDL_SYSTEM_THEME_DARK:
                return SystemTheme::Dark;
            case SDL_SYSTEM_THEME_LIGHT:
                return SystemTheme::Light;
            default:
                return SystemTheme::Unknown;
        }
    }


}
