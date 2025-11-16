#include "Vertex.h"

namespace circuits {

    Vertex::Vertex(const glm::vec2& pos, const Color& color)
        : pos(pos), col(color.asVec4()) {}

    Vertex::Vertex(const glm::vec2& pos, const glm::vec2& uv)
        : pos(pos), col(uv, glm::vec2(0)) {}

}