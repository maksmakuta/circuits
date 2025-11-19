#include "Rect.h"

namespace circuits {

    Rect::Rect() = default;

    Rect::Rect(const int _x, const int _y, const int _w, const int _h)
        : position(_x,_y), size(_w,_h) {}

    Rect::Rect(const Position& pos, const Size& size)
        : position(pos), size(size) {}

    Rect::Rect(const glm::ivec2& pos, const glm::ivec2& size)
        : position(pos.x,pos.y), size(size.x, size.y) {}

    Rect::Rect(const glm::ivec4& v)
        : position(v.x, v.y), size(v.z, v.w) {}

    glm::vec2 Rect::getCenter() const {
        return position.toIVec2() + glm::ivec2(size.width, size.height) / 2;
    }

    bool Rect::in(const glm::ivec2& vec) const {
        return vec.x >= position.x && vec.x <= position.x + size.width && vec.y >= position.y && vec.y <= position.y + size.height;
    }

}
