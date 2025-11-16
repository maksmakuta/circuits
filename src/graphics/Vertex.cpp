#include "Vertex.h"

namespace circuits {

    Vertex::Vertex(const glm::vec2& pos, const Color& color)
        : pos(pos), uv{0}, col(color.asVec4()) {}

    Vertex::Vertex(const glm::vec2& pos, const glm::vec2& uv, const Color& color)
        : pos(pos), uv(uv), col(color.asVec4()) {}

}