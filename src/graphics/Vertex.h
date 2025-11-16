#ifndef CIRCUITS_VERTEX_H
#define CIRCUITS_VERTEX_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Color.h"

namespace circuits {

    struct Vertex {
        Vertex(const glm::vec2& pos, const Color& color);
        Vertex(const glm::vec2& pos, const glm::vec2& uv, const Color& color = {});

        glm::vec2 pos;
        glm::vec2 uv;
        glm::vec4 col;
    };

}

#endif //CIRCUITS_VERTEX_H