#ifndef CIRCUITS_RECT_H
#define CIRCUITS_RECT_H

#include <glm/vec4.hpp>

#include "Position.h"
#include "Size.h"

namespace circuits {

    struct Rect {
        Rect();
        Rect(int _x, int _y, int _w, int _h);
        Rect(const Position& pos, const Size& size);
        Rect(const glm::ivec2& pos, const glm::ivec2& size);

        explicit Rect(const glm::ivec4&);

        [[nodiscard]] glm::vec2 getCenter() const;
        [[nodiscard]] bool in(const glm::ivec2& vec) const;

        Position position;
        Size size;
    };

}

#endif //CIRCUITS_RECT_H