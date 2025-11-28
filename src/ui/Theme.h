#ifndef CIRCUITS_THEME_H
#define CIRCUITS_THEME_H

#include "enums/ThemeName.h"
#include "graphics/Color.h"
#include "graphics/Font.h"

namespace circuits {

    struct Palette {
        Color primary;
        Color secondary;
        Color surface;
        Color surfaceVariant;
        Color background;
        Color error;
        Color outline;

        Color onPrimary;
        Color onSecondary;
        Color onSurface;
        Color onSurfaceVariant;
        Color onBackground;
        Color onError;
    };

    struct Shape {
        float cornerSmall;
        float cornerMedium;
        float cornerLarge;

        float borderThickness;
        float borderRadius;
    };

    struct StateLayer {
        float hoverOpacity  = 0.12f;
        float pressOpacity  = 0.20f;
        float disabledAlpha = 0.38f;
    };

    struct Typography {
        Font title;
        Font body;
        Font label;
    };

    struct Theme {
        Shape shape{};
        Palette palette{};
        StateLayer layer{};
        Typography typography{};
        ThemeName theme = ThemeName::Unknown;

        static Theme getTheme(ThemeName systemTheme = ThemeName::Unknown);
        static Theme getDarkTheme();
        static Theme getLightTheme();
    };

}

#endif //CIRCUITS_THEME_H