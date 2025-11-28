#ifndef CIRCUITS_COLOR_H
#define CIRCUITS_COLOR_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace circuits {

    class Color {
    public:
        Color() = default;
        explicit Color(glm::uint color);
        explicit Color(const glm::vec3& color);
        explicit Color(const glm::vec4& color);
        explicit Color(float r, float g, float b, float a = 1.f);

        static Color fromBytes(int r, int g, int b, int a = 255);
        static Color blend(const Color& base, const Color& overlay);

        [[nodiscard]] glm::vec4 asVec4() const;
        [[nodiscard]] glm::vec3 asVec3() const;
        [[nodiscard]] glm::uint asHex() const;
        [[nodiscard]] Color withAlpha(float a) const;

        float& r() { return m_color[0]; }
        float& g() { return m_color[1]; }
        float& b() { return m_color[2]; }
        float& a() { return m_color[3]; }

    private:
        glm::vec4 m_color{0,0,0,1};
    };

}

#endif //CIRCUITS_COLOR_H