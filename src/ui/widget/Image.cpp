#include "Image.h"

namespace circuits {

    Image::Image(const Texture& t, const glm::vec2& uv_a, const glm::vec2& uv_b, const glm::ivec2& s)
        :IWidget(), m_texture(t), m_uv_min(uv_a), m_uv_max(uv_b), m_size(s) {}

    glm::ivec2 Image::onMeasure(const glm::ivec2 &max) {
        if (m_size == glm::ivec2(-1)) {
            const glm::vec2 size = m_texture.getSize();
            const auto a = size * m_uv_min;
            const auto b = size * m_uv_max;
            return b - a;
        }
        return m_size;
    }

    void Image::onDraw(Renderer& r) {
        r.rect(getRect().pos,getRect().size);
        r.fill(m_texture,m_uv_min,m_uv_max);
    }

}