#include "Theme.h"

#include <SDL3/SDL_video.h>

namespace circuits {

    Theme Theme::getTheme(const SystemTheme systemTheme) {
        if (systemTheme == SystemTheme::Unknown) {
            if (SDL_GetSystemTheme() == SDL_SYSTEM_THEME_DARK) {
                return getDarkTheme();
            }
            return getLightTheme();
        }
        if (systemTheme == SystemTheme::Dark) {
            return getDarkTheme();
        }
        return getLightTheme();
    }

    Theme Theme::getDarkTheme() {
        Theme t = getLightTheme();

        t.theme = SystemTheme::Dark;

        t.palette.primary           = Color::fromBytes(187, 134, 252);
        t.palette.onPrimary         = Color::fromBytes(33 , 25 , 40 );
        t.palette.secondary         = Color::fromBytes(185, 157, 222);
        t.palette.onSecondary       = Color::fromBytes(33 , 25 , 40 );
        t.palette.surface           = Color::fromBytes(28 , 24 , 30 );
        t.palette.onSurface         = Color::fromBytes(222, 216, 230);
        t.palette.surfaceVariant    = Color::fromBytes(56 , 49 , 62 );
        t.palette.onSurfaceVariant  = Color::fromBytes(204, 198, 213);
        t.palette.outline           = Color::fromBytes(98 , 92 , 106);
        t.palette.background        = Color::fromBytes(18 , 16 , 21 );
        t.palette.onBackground      = Color::fromBytes(222, 216, 230);
        t.palette.error             = Color::fromBytes(255, 102, 102);
        t.palette.onError           = Color::fromBytes(33 , 25 , 40 );

        return t;
    }

    Theme Theme::getLightTheme() {
        Theme t;
        t.theme = SystemTheme::Light;

        t.palette.primary           = Color::fromBytes(103, 80 , 164 );
        t.palette.onPrimary         = Color::fromBytes(255, 255, 255 );

        t.palette.secondary         = Color::fromBytes(216, 185, 255 );
        t.palette.onSecondary       = Color::fromBytes(33 , 25 , 40  );

        t.palette.surface           = Color::fromBytes(255, 251, 254 );
        t.palette.onSurface         = Color::fromBytes(33 , 25 , 40  );

        t.palette.surfaceVariant    = Color::fromBytes(232, 222, 248 );
        t.palette.onSurfaceVariant  = Color::fromBytes(71 , 63 , 79  );

        t.palette.background        = Color::fromBytes(255, 255, 255 );
        t.palette.onBackground      = Color::fromBytes(33 , 25 , 40  );

        t.palette.error             = Color::fromBytes(179, 38 , 30  );
        t.palette.onError           = Color::fromBytes(255, 255, 255 );

        t.palette.outline           = Color::fromBytes(146, 143, 154 );

        t.shape.cornerSmall         = 4.0f;
        t.shape.cornerMedium        = 8.0f;
        t.shape.cornerLarge         = 16.0f;

        t.shape.borderThickness     = 2.0f;
        t.shape.borderRadius        = 12.0f;

        t.typography.title.loadDefault(28);
        t.typography.body.loadDefault(24);
        t.typography.label.loadDefault(20);

        return t;
    }

}
