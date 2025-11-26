#ifndef CIRCUITS_CURSOR_H
#define CIRCUITS_CURSOR_H

#include <cstdint>

namespace circuits {

    enum class Cursor : uint8_t{
        Default,
        No,
        Hand,
        Text,
        Move,
        Wait,
        ResizeH,
        ResizeV
    };

}

#endif //CIRCUITS_CURSOR_H