#ifndef CIRCUITS_PATH_H
#define CIRCUITS_PATH_H

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace circuits {

    class Path {
    public:
        Path() = default;

        Path& moveTo(const glm::vec2& p);
        Path& lineTo(const glm::vec2& p);
        Path& quadTo(const glm::vec2& c, const glm::vec2& p);
        Path& cubicTo(const glm::vec2& c1, const glm::vec2& c2, const glm::vec2& p);
        Path& arcTo(const glm::vec2& center, float radius, float startAngle, float endAngle, bool ccw = false);
        Path& close();

        Path& clear();
        [[nodiscard]] bool empty() const { return m_data.empty(); }
        [[nodiscard]] size_t size() const { return m_data.size(); }
        [[nodiscard]] bool isClosed() const { return m_closed; }

        Path& translate(const glm::vec2& offset);
        Path& scale(const glm::vec2& s);
        Path& rotate(float radians, const glm::vec2& origin = {0, 0});

        [[nodiscard]] glm::vec2 getPoint(const size_t index) const { return m_data[index]; }
        [[nodiscard]] const std::vector<glm::vec2>& points() const { return m_data; }

        [[nodiscard]] glm::vec2 boundsMin() const;
        [[nodiscard]] glm::vec2 boundsMax() const;
        [[nodiscard]] glm::vec2 center() const;

        [[nodiscard]] float length() const;
        [[nodiscard]] glm::vec2 positionAt(float t) const;
        [[nodiscard]] glm::vec2 directionAt(float t) const;

        [[nodiscard]] glm::vec2 last() const;
        [[nodiscard]] glm::vec2 first() const;

        static Path line(const glm::vec2& a, const glm::vec2& b);
        static Path rectangle(const glm::vec2& pos, const glm::vec2& size);
        static Path roundedRect(const glm::vec2& pos, const glm::vec2& size, float radius, int cornerSegments = 8);
        static Path roundedRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& radius, int cornerSegments = 8);
        static Path roundedRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& radius, int cornerSegments = 8);
        static Path circle(const glm::vec2& center, float radius, int segments = 32);
        static Path ellipse(const glm::vec2& center, const glm::vec2& radii, int segments = 32);

    private:
        std::vector<glm::vec2> m_data;
        bool m_closed = false;
    };

}

#endif //CIRCUITS_PATH_H