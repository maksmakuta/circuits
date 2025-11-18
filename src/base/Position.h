#ifndef CIRCUITS_POSITION_H
#define CIRCUITS_POSITION_H

#include <glm/vec2.hpp>

namespace circuits {

    struct Position{
        Position();
        Position(int _x, int _y);

        explicit Position(int a);

        [[nodiscard]] glm::ivec2 toIVec2() const;

        int x, y;
    };

}

#endif //CIRCUITS_POSITION_H