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

    bool Rect::isEmpty() const {
        return size.x <= 0 || size.y <= 0;
    }

    bool Rect::contains(const glm::ivec2& p) const {
        return p.x >= left() && p.y >= top() && p.x < right() && p.y < bottom();
    }

    bool Rect::intersects(const Rect& o) const {
        return !(o.left() >= right() || o.right() <= left() || o.top() >= bottom() || o.bottom() <= top());
    }

    Rect Rect::translated(const glm::ivec2& t) const {
        return Rect{pos + t, size};
    }

    Rect Rect::inset(const glm::ivec2& padLT, const glm::ivec2& padRB) const {
        const glm::ivec2 newPos = pos + padLT;
        glm::ivec2 newSize = size - (padLT + padRB);
        if (newSize.x < 0) newSize.x = 0;
        if (newSize.y < 0) newSize.y = 0;
        return Rect{newPos, newSize};
    }

    Rect Rect::deflate(const glm::ivec4& p) const {
        return inset({p.x, p.y}, {p.z, p.w});
    }

    Rect Rect::centeredIn(const Rect& container) const {
        const glm::ivec2 posCentered = container.pos + (container.size - size) / 2;
        return Rect{posCentered, size};
    }

    Rect Rect::intersectionWith(const Rect& o) const {
        const glm::ivec2 tl{ std::max(left(), o.left()), std::max(top(), o.top()) };
        const glm::ivec2 br{ std::min(right(), o.right()), std::min(bottom(), o.bottom()) };
        if (br.x <= tl.x || br.y <= tl.y) return Rect{};
        return fromCorners(tl, br);
    }

    Rect Rect::unionWith(const Rect& o) const {
        if (isEmpty()) return o;
        if (o.isEmpty()) return *this;
        const glm::ivec2 tl{ std::min(left(), o.left()), std::min(top(), o.top()) };
        const glm::ivec2 br{ std::max(right(), o.right()), std::max(bottom(), o.bottom()) };
        return fromCorners(tl, br);
    }

}