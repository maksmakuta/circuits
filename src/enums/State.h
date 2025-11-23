#ifndef CIRCUITS_STATE_H
#define CIRCUITS_STATE_H

#include <cstdint>

namespace circuits {

    enum class State : uint8_t {
        Normal,
        Hover,
        Active,
        Disable
    };

}

#endif //CIRCUITS_STATE_H