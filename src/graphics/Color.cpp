#include "Color.h"

#include <glm/glm.hpp>

namespace circuits {

    Color::Color() = default;

    Color::Color(const glm::uint32& hex) {
        const uint8_t a = (hex >> 24) & 0xFF;
        const uint8_t r = (hex >> 16) & 0xFF;
        const uint8_t g = (hex >>  8) & 0xFF;
        const uint8_t b = (hex >>  0) & 0xFF;
        m_data = glm::vec4{ r, g, b, a } / 255.f;
    }

    Color::Color(const glm::vec3& vec3) : m_data(glm::vec4{ vec3, 1.f }){}

    Color::Color(const glm::vec4& vec4) : m_data(vec4) {}

    Color::Color(const float r, const float g, const float b) : m_data{ r, g, b ,1.f} {}

    Color::Color(const float r, const float g, const float b, const float a) : m_data{ r, g, b, a } {}

    Color Color::operator+(const Color& other) const {
        return Color{glm::normalize(m_data + other.m_data)};
    }

    Color Color::operator-(const Color& other) const {
        return Color{glm::normalize(m_data - other.m_data)};
    }

    Color Color::operator*(const Color& other) const {
        return Color{glm::normalize(m_data * other.m_data)};
    }

    Color Color::operator*(const float scalar) const {
        return Color{glm::normalize(m_data * scalar)};
    }

    Color Color::operator/(const float scalar) const {
        return Color{glm::normalize(m_data / scalar)};
    }

    Color& Color::operator+=(const Color& other) {
        *this = *this + other;
        return *this;
    }

    Color& Color::operator*=(float scalar) {
        *this = *this * scalar;
        return *this;
    }

    Color Color::premultiplied() const {
        return {r()*a(), g()*a(), b()*a(), a()};
    }

    Color Color::grayscale() const {
        return {luminance(), luminance(), luminance(), a()};
    }

    Color Color::inverted() const {
        return {1.f - r(), 1.f - g(), 1.f - b(), a()};
    }

    float Color::luminance() const {
        return 0.2126f * r() + 0.7152f * g() + 0.0722f * b();
    }

    uint32_t Color::pack() const {
        const auto bytes = glm::u32vec4(m_data * 255.f);
        return bytes[3] << 24 | bytes[0] << 16 | bytes[1] << 8 | bytes[2];
    }

    float Color::r() const { return m_data.r; }
    float Color::g() const { return m_data.g; }
    float Color::b() const { return m_data.b; }
    float Color::a() const { return m_data.a; }

    Color Color::mix(const Color& a,const Color& b, const float t) {
        return Color{glm::mix(a.m_data, b.m_data, t)};
    }

}