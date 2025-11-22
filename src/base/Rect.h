#ifndef CIRCUITS_RECT_H
#define CIRCUITS_RECT_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace circuits {

    struct Rect final {
        Rect() = default;
        Rect(const glm::ivec2& p, const glm::ivec2& s);

        static Rect fromCorners(const glm::ivec2& tl, const glm::ivec2& br);

        [[nodiscard]] int left() const;
        [[nodiscard]] int top() const;
        [[nodiscard]] int right() const;
        [[nodiscard]] int bottom() const;

        [[nodiscard]] bool isEmpty() const;

        [[nodiscard]] bool contains(const glm::ivec2& p) const;
        [[nodiscard]] bool intersects(const Rect& o) const;

        [[nodiscard]] Rect translated(const glm::ivec2& t) const;

        [[nodiscard]] Rect inset(const glm::ivec2& padLT, const glm::ivec2& padRB) const;
        [[nodiscard]] Rect deflate(const glm::ivec4& p) const;

        [[nodiscard]] Rect centeredIn(const Rect& container) const;
        [[nodiscard]] Rect intersectionWith(const Rect& o) const;
        [[nodiscard]] Rect unionWith(const Rect& o) const;

        glm::ivec2 pos{0,0};
        glm::ivec2 size{0,0};
    };

}

#endif //CIRCUITS_RECT_H