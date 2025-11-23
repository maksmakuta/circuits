#ifndef CIRCUITS_SIZEUNIT_H
#define CIRCUITS_SIZEUNIT_H

#include <cstdint>

namespace circuits {

    enum class SizeUnit : uint8_t{
        Auto,
        Fill,
        Fixed,
        Percent
    };

}

#endif //CIRCUITS_SIZEUNIT_H