#include "Rect.h"

namespace circuits {

    Rect::Rect() = default;

    Rect::Rect(const glm::ivec2& p, const glm::ivec2& s) : pos(p), size(s) {}

    Rect Rect::fromPoints(const glm::ivec2& p0, const glm::ivec2& p1) {
        return {p0, p1 - p0};
    }

    bool Rect::contains(const glm::ivec2 &p) const {
        const auto p1 = glm::ivec2(pos);
        const auto p2 = p1 + glm::ivec2(size);
        return p.x >= p1.x && p.x <= p2.x && p.y >= p1.y && p.y <= p2.y;
    }

}
