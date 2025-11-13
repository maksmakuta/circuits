#ifndef CIRCUITS_VERTEX_H
#define CIRCUITS_VERTEX_H

#include <glm/glm.hpp>

namespace circuits {

    struct Vertex {
        Vertex() = default;
        explicit Vertex(const glm::vec2& p);
        Vertex(const glm::vec2& p,const glm::vec4& c);
        Vertex(const glm::vec2& p, const glm::vec2& t, const glm::vec4& c);

        static void setupAttributes();

        glm::vec2 pos   = {0.0f, 0.0f};
        glm::vec2 uv    = {0.0f, 0.0f};
        glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    };

}

#endif //CIRCUITS_VERTEX_H