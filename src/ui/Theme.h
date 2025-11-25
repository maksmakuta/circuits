#ifndef CIRCUITS_THEME_H
#define CIRCUITS_THEME_H

#include "enums/ThemeName.h"
#include "graphics/Color.h"
#include "graphics/Font.h"

namespace circuits {

    struct Palette {
        Color primary;
        Color onPrimary;

        Color secondary;
        Color onSecondary;

        Color surface;
        Color onSurface;

        Color surfaceVariant;
        Color onSurfaceVariant;

        Color outline;

        Color background;
        Color onBackground;

        Color error;
        Color onError;
    };

    struct Shape {
        float cornerSmall;
        float cornerMedium;
        float cornerLarge;

        float borderThickness;
        float borderRadius;
    };

    struct Typography {
        Font title;
        Font body;
        Font label;
    };

    struct Theme {
        Shape shape;
        Palette palette;
        Typography typography;
        ThemeName theme = ThemeName::Unknown;

        static Theme getTheme(ThemeName systemTheme = ThemeName::Unknown);
        static Theme getDarkTheme();
        static Theme getLightTheme();
    };

}

#endif //CIRCUITS_THEME_H