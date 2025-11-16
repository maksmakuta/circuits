#include "Color.h"

namespace circuits {

    Color::Color(const glm::vec3& color) : m_color(color, 1.f) {}
    Color::Color(const glm::vec4& color) : m_color(color) {}
    Color::Color(const float r, const float g, const float b, const float a) : Color(glm::vec4(r, g, b, a)) {}

    Color::Color(const glm::uint color) {
        const auto a = (color >> 24) & 0xFF;
        const auto r = (color >> 16) & 0xFF;
        const auto g = (color >>  8) & 0xFF;
        const auto b = (color >>  0) & 0xFF;
        m_color = glm::vec4(r, g, b, a) / 255.f;
    }

    glm::vec4 Color::asVec4() const{
        return m_color;
    }

    glm::vec3 Color::asVec3() const{
        return {m_color.r, m_color.g, m_color.b};
    }

    glm::uint Color::asHex() const{
        const auto c = glm::uvec4(m_color * 255.f);
        return c.a << 24 | c.b << 16 | c.g << 8 | c.b;
    }

}