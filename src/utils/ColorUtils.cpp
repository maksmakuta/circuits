#include "ColorUtils.h"

#include "core/Modifier.h"

namespace circuits {

    Color ColorUtils::getBaseColor(const Appearance a) {
        switch (a) {
            case Appearance::Surface:
                return currentTheme().palette.surface;

            case Appearance::SurfaceVariant:
                return currentTheme().palette.surfaceVariant;

            case Appearance::Primary:
                return currentTheme().palette.primary;

            case Appearance::Secondary:
                return currentTheme().palette.secondary;

            case Appearance::Error:
                return currentTheme().palette.error;

            default:
                return currentTheme().palette.background;
        }
    }

    Color ColorUtils::getBaseOnColor(const Appearance a) {
        switch (a) {
            case Appearance::Surface:
                return currentTheme().palette.onSurface;

            case Appearance::SurfaceVariant:
                return currentTheme().palette.onSurfaceVariant;

            case Appearance::Primary:
                return currentTheme().palette.onPrimary;

            case Appearance::Secondary:
                return currentTheme().palette.onSecondary;

            case Appearance::Error:
                return currentTheme().palette.onError;

            default:
                return currentTheme().palette.onBackground;
        }
    }

    Color ColorUtils::resolveColor(const Appearance a, const State s) {
        const auto t = currentTheme();
        const Color base = getBaseColor(a);
        const Color on_base = getBaseOnColor(a);
        switch (s) {
            case State::Disabled:
                return base.withAlpha(t.layer.disabledAlpha);

            case State::Hovered:
                return Color::blend(base, on_base.withAlpha(t.layer.hoverOpacity));

            case State::Pressed:
                return Color::blend(base, on_base.withAlpha(t.layer.pressOpacity));

            default:
                return base;
        }
    }
}
