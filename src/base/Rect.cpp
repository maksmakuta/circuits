#include "Rect.h"

namespace circuits {

    Rect::Rect(const glm::ivec2& p, const glm::ivec2& s)
        : pos(p), size(s) {}

    Rect Rect::fromCorners(const glm::ivec2& tl, const glm::ivec2& br) {
        return {tl, br - tl};
    }

    int Rect::left() const { return pos.x; }
    int Rect::top() const { return pos.y; }
    int Rect::right() const { return pos.x + size.x; }
    int Rect::bottom() const { return pos.y + size.y; }

    bool Rect::contains(const glm::ivec2& p) const {
        return p.x >= left() && p.y >= top() && p.x < right() && p.y < bottom();
    }

    bool Rect::intersects(const Rect& o) const {
        return !(o.left() >= right() || o.right() <= left() || o.top() >= bottom() || o.bottom() <= top());
    }

}