#ifndef CIRCUITS_COLOR_H
#define CIRCUITS_COLOR_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace circuits {

    class Color {
    public:
        Color();
        explicit Color(const glm::uint32&);
        explicit Color(const glm::vec3&);
        explicit Color(const glm::vec4&);
        Color(float r, float g, float b);
        Color(float r, float g, float b, float a);

        Color operator+(const Color& other) const;
        Color operator-(const Color& other) const;
        Color operator*(const Color& other) const;
        Color operator*(float scalar) const;
        Color operator/(float scalar) const;

        Color& operator+=(const Color& other);
        Color& operator*=(float scalar);

        [[nodiscard]] Color premultiplied() const;
        [[nodiscard]] Color grayscale() const;
        [[nodiscard]] Color inverted() const;

        [[nodiscard]] float luminance() const;
        [[nodiscard]] uint32_t pack() const;

        [[nodiscard]] float r() const;
        [[nodiscard]] float g() const;
        [[nodiscard]] float b() const;
        [[nodiscard]] float a() const;

        static Color mix(const Color& a,const Color& b, float t);
    private:
        glm::vec4 m_data{0,0,0,1};
    };

}

#endif //CIRCUITS_COLOR_H