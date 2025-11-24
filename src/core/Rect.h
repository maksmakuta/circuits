#ifndef CIRCUITS_RECT_H
#define CIRCUITS_RECT_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace circuits {

    struct Rect final {
        Rect();
        Rect(const glm::ivec2& p, const glm::ivec2& s);

        static Rect fromPoints(const glm::ivec2& p0, const glm::ivec2& p1);

        [[nodiscard]] bool contains(const glm::ivec2& p) const;

        glm::ivec2 pos{0};
        glm::ivec2 size{0};
    };

}

#endif //CIRCUITS_RECT_H