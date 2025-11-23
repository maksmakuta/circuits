#ifndef CIRCUITS_GRAVITY_H
#define CIRCUITS_GRAVITY_H

#include <cstdint>

namespace circuits {

    enum class Gravity : uint32_t {
        None        = 0,
        Left        = 1 << 0,
        HCenter     = 1 << 1,
        Right       = 1 << 2,
        Top         = 1 << 4,
        VCenter     = 1 << 5,
        Bottom      = 1 << 6,
        Center      = HCenter   | VCenter,
        TopLeft     = Top       | Left,
        TopRight    = Top       | Right,
        BottomLeft  = Bottom    | Left,
        BottomRight = Bottom    | Right,
    };

    inline Gravity operator|(Gravity a, Gravity b) {
        return static_cast<Gravity>(
            static_cast<uint32_t>(a) | static_cast<uint32_t>(b)
        );
    }

    inline Gravity operator&(Gravity a, Gravity b) {
        return static_cast<Gravity>(
            static_cast<uint32_t>(a) & static_cast<uint32_t>(b)
        );
    }

    inline Gravity& operator|=(Gravity& a, Gravity b) {
        a = a | b;
        return a;
    }

    inline bool any(Gravity g, Gravity mask) {
        return (static_cast<uint32_t>(g) &
                static_cast<uint32_t>(mask)) != 0;
    }

}

#endif //CIRCUITS_GRAVITY_H