#include "Color.h"

#include <glm/common.hpp>

namespace circuits {

    Color::Color(const glm::vec3& color) : m_color(color, 1.f) {}
    Color::Color(const glm::vec4& color) : m_color(color) {}
    Color::Color(const float r, const float g, const float b, const float a) : Color(glm::vec4(r, g, b, a)) {}

    Color Color::fromBytes(const int r, const int g, const int b, const int a) {
        const auto rf = static_cast<float>(r) / 255.f;
        const auto gf = static_cast<float>(g) / 255.f;
        const auto bf = static_cast<float>(b) / 255.f;
        const auto af = static_cast<float>(a) / 255.f;
        return Color{rf,gf,bf,af};
    }

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
        return c.a << 24 | c.r << 16 | c.g << 8 | c.b;
    }

    Color Color::withAlpha(const float a) const {
        return Color(glm::vec4{asVec3(), a});
    }

    Color Color::blend(const Color &base, const Color &overlay) {
        const float oa = overlay.asVec4().a;
        return Color(
            glm::vec4{
                glm::mix(base.asVec3(), overlay.asVec3(), oa),
                1.0f
            }
        );
    }
}
