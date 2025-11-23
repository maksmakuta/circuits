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

        [[nodiscard]] bool contains(const glm::ivec2& p) const;
        [[nodiscard]] bool intersects(const Rect& o) const;

        glm::ivec2 pos{0,0};
        glm::ivec2 size{0,0};
    };

}

#endif //CIRCUITS_RECT_H