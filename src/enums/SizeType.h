#ifndef CIRCUITS_SIZETYPE_H
#define CIRCUITS_SIZETYPE_H

#include <cstdint>

namespace circuits {

    enum class SizeType : uint8_t {
        Auto,
        Fixed,
        Fill,
        Percent
    };

}

#endif //CIRCUITS_SIZETYPE_H