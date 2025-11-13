#include "Vertex.h"

#include "glad/gl.h"

namespace circuits {

    Vertex::Vertex(const glm::vec2& p, const glm::vec2& t, const glm::vec4& c) : pos(p), uv(t), color(c) {}
    Vertex::Vertex(const glm::vec2& p) : pos(p), uv(0.0f), color(1.0f) {}
    Vertex::Vertex(const glm::vec2& p,const glm::vec4& c) : pos(p), uv(0.0f), color(c) {}

    void Vertex::setupAttributes() {
        constexpr GLsizei stride = sizeof(Vertex);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offsetof(Vertex, pos)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offsetof(Vertex, uv)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offsetof(Vertex, color)));
    }

}
