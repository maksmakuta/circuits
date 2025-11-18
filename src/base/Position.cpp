#include "Position.h"

namespace circuits {

    Position::Position() : x(0), y(0) {}
    Position::Position(const int a) : x(a), y(a) {}
    Position::Position(const int _x, const int _y) : x(_x), y(_y) {}

    glm::ivec2 Position::toIVec2() const {
        return {x, y};
    }

}