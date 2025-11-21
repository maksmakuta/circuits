#ifndef CIRCUITS_JOINT_H
#define CIRCUITS_JOINT_H

#include <cstdint>

namespace circuits {

    enum class Joint : uint8_t {
        Miter,
        Bevel,
        Round
    };

}

#endif //CIRCUITS_JOINT_H