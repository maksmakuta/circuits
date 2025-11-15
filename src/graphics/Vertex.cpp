#include "Vertex.h"

#include "glad/gl.h"

namespace circuits {

    Vertex::Vertex(const glm::vec2& p, const glm::vec2& t, const glm::vec4& c) : pos(p), uv(t), color(c * 255.f) {}
    Vertex::Vertex(const glm::vec2& p) : pos(p), uv(0.0f), color(1.0f) {}
    Vertex::Vertex(const glm::vec2& p,const glm::vec4& c, const int op) : pos(p), uv(0.0f), color(c * 255.f), data(op) {}
    Vertex::Vertex(const glm::vec2& p,const glm::vec4& c) : pos(p), uv(0.0f), color(c * 255.f) {}

    void Vertex::setupAttributes() {
        constexpr GLsizei stride = sizeof(Vertex);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, stride, reinterpret_cast<void *>(offsetof(Vertex, pos)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_UNSIGNED_SHORT, GL_TRUE, stride, reinterpret_cast<void *>(offsetof(Vertex, uv)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, reinterpret_cast<void *>(offsetof(Vertex, color)));

        glEnableVertexAttribArray(3);
        glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, stride, reinterpret_cast<void *>(offsetof(Vertex, data)));
    }

}
