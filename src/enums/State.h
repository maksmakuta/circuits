#ifndef CIRCUITS_STATE_H
#define CIRCUITS_STATE_H

#include <cstdint>

namespace circuits {

    enum class State : uint8_t {
        Enabled,
        Disabled,
        Hovered,
        Pressed
    };

}

#endif //CIRCUITS_STATE_H