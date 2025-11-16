#include "Path.h"

#include <algorithm>
#include <cmath>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/constants.hpp>

namespace circuits {
    Path& Path::moveTo(const glm::vec2& p) {
        clear();
        m_points.push_back(p);
        m_closed = false;
        return *this;
    }

    Path& Path::lineTo(const glm::vec2& p) {
        m_points.push_back(p);
        return *this;
    }

    Path& Path::quadTo(const glm::vec2& c, const glm::vec2& p) {
        if (m_points.empty()) return moveTo(p);
        const glm::vec2 start = m_points.back();
        constexpr int segments = 16;
        for (int i = 1; i <= segments; ++i) {
            const float t = static_cast<float>(i) / static_cast<float>(segments);
            glm::vec2 q = (1 - t)*(1 - t)*start + 2*(1 - t)*t*c + t*t*p;
            m_points.push_back(q);
        }
        return *this;
    }

    Path& Path::cubicTo(const glm::vec2& c1, const glm::vec2& c2, const glm::vec2& p) {
        if (m_points.empty()) return moveTo(p);
        const glm::vec2 start = m_points.back();
        constexpr int segments = 24;
        for (int i = 1; i <= segments; ++i) {
            const float t = static_cast<float>(i) / static_cast<float>(segments);
            glm::vec2 q = std::powf(1 - t, 3) * start +
                          3 * std::powf(1 - t, 2) * t * c1 +
                          3 * (1 - t) * t * t * c2 +
                          t * t * t * p;
            m_points.push_back(q);
        }
        return *this;
    }

    Path& Path::arcTo(const glm::vec2& center, const glm::vec2& radius, const float startAngle, const float endAngle, const bool ccw) {
        constexpr int segments = 32;
        float delta = endAngle - startAngle;
        if (ccw && delta > 0) delta -= glm::two_pi<float>();
        if (!ccw && delta < 0) delta += glm::two_pi<float>();

        for (int i = 0; i <= segments; ++i) {
            const float t = static_cast<float>(i) / segments;
            const float angle = startAngle + delta * t;
            glm::vec2 p = center + glm::vec2(std::cos(angle), std::sin(angle)) * radius;
            m_points.push_back(p);
        }
        return *this;
    }

    Path& Path::close() {
        if (!m_points.empty()) {
            m_closed = true;
        }
        return *this;
    }

    void Path::clear() {
        m_points.clear();
    }

    void Path::reverse() {
        std::ranges::reverse(m_points);
    }

    bool Path::isClosed() const {
        return m_closed;
    }

    bool Path::empty() const {
        return m_points.empty();
    }

    size_t Path::size() const {
        return m_points.size();
    }

    glm::vec2 Path::boundsMin() const {
        auto min = glm::vec2(0);
        for (const auto& p : m_points) {
            min = glm::min(min, p);
        }
        return min;
    }

    glm::vec2 Path::boundsMax() const {
        auto max = glm::vec2(0);
        for (const auto& p : m_points) {
            max = glm::max(max, p);
        }
        return max;
    }

    glm::vec2 Path::center() const {
        return (boundsMin() + boundsMax()) / 2.f;
    }

    std::vector<glm::vec2> Path::points() const {
        return m_points;
    }

    Path& Path::translate(const glm::vec2& offset) {
        for (auto& p : m_points) {
            p += offset;
        }
        return *this;
    }

    Path& Path::scale(const glm::vec2& s) {
        for (auto& p : m_points) {
            p *= s;
        }
        return *this;
    }

    Path& Path::scale(const float s) {
        for (auto& p : m_points) {
            p *= s;
        }
        return *this;
    }

    Path& Path::rotate(const float radians, const glm::vec2& origin) {
        for (auto& p : m_points) {
            p = glm::rotate(p - origin, radians);
        }
        return *this;
    }

}
