#ifndef CIRCUITS_VERTEX_H
#define CIRCUITS_VERTEX_H

#include <glm/glm.hpp>

namespace circuits {

    struct Vertex {
        Vertex() = default;
        explicit Vertex(const glm::vec2& p);
        Vertex(const glm::vec2& p,const glm::vec4& c);
        Vertex(const glm::vec2& p,const glm::vec4& c, int op);
        Vertex(const glm::vec2& p, const glm::vec2& t, const glm::vec4& c);

        static void setupAttributes();

        glm::i16vec2    pos   = {0.0f, 0.0f};
        glm::u16vec2    uv    = {0.0f, 0.0f};
        glm::u8vec4     color = {255, 255, 255, 255};
        glm::uint       data  = 0;

    };

}

#endif //CIRCUITS_VERTEX_H