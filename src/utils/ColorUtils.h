#ifndef CIRCUITS_COLORUTILS_H
#define CIRCUITS_COLORUTILS_H

#include "enums/Appearance.h"
#include "enums/State.h"
#include "graphics/Color.h"

namespace circuits {

    class ColorUtils {
    public:
        static Color getBaseColor(Appearance);
        static Color getBaseOnColor(Appearance);
        static Color resolveColor(Appearance,State);
    };

}



#endif //CIRCUITS_COLORUTILS_H