#ifndef CIRCUITS_PATH_H
#define CIRCUITS_PATH_H

#include <vector>
#include <glm/vec2.hpp>

namespace circuits {

    class Path {
    public:
        Path() = default;

        Path& moveTo(const glm::vec2&);
        Path& lineTo(const glm::vec2&);
        Path& quadTo(const glm::vec2&, const glm::vec2&);
        Path& cubicTo(const glm::vec2&, const glm::vec2& , const glm::vec2& );
        Path& arcTo(const glm::vec2&, const glm::vec2&, float, float, bool = false);
        Path& close();

        Path& translate(const glm::vec2& offset);
        Path& scale(const glm::vec2& s);
        Path& scale(float s);
        Path& rotate(float radians, const glm::vec2& origin = {0,0});

        void clear();
        void reverse();

        [[nodiscard]] bool isClosed() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] size_t size() const;

        [[nodiscard]] glm::vec2 boundsMin() const;
        [[nodiscard]] glm::vec2 boundsMax() const;
        [[nodiscard]] glm::vec2 center() const;

        [[nodiscard]] std::vector<glm::vec2> points() const;

    private:
        std::vector<glm::vec2> m_points;
        bool m_closed = false;
    };

}


#endif //CIRCUITS_PATH_H