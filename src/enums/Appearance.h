#ifndef CIRCUITS_TEXTAPPEARANCE_H
#define CIRCUITS_TEXTAPPEARANCE_H

#include <cstdint>

namespace circuits {

    enum class Appearance : uint8_t{
        Normal,
        Surface,
        SurfaceVariant,
        Primary,
        Secondary,
        Error
    };

}

#endif //CIRCUITS_TEXTAPPEARANCE_H