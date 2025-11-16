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

        [[nodiscard]] glm::vec4 asVec4() const;
        [[nodiscard]] glm::vec3 asVec3() const;
        [[nodiscard]] glm::uint asHex() const;

    private:
        glm::vec4 m_color{0,0,0,1};
    };

}

#endif //CIRCUITS_COLOR_H