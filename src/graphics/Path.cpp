#include "Path.h"

#include <algorithm>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

namespace circuits {
    
    Path& Path::moveTo(const glm::vec2& p) {
        m_data.clear();
        m_data.push_back(p);
        m_closed = false;
        return *this;
    }

    Path& Path::lineTo(const glm::vec2& p) {
        m_data.push_back(p);
        return *this;
    }

    Path& Path::quadTo(const glm::vec2& c, const glm::vec2& p) {
        if (m_data.empty()) return moveTo(p);
        const glm::vec2 start = m_data.back();
        constexpr int segments = 16;
        for (int i = 1; i <= segments; ++i) {
            const float t = static_cast<float>(i) / static_cast<float>(segments);
            glm::vec2 q = (1 - t)*(1 - t)*start + 2*(1 - t)*t*c + t*t*p;
            m_data.push_back(q);
        }
        return *this;
    }

    Path& Path::cubicTo(const glm::vec2& c1, const glm::vec2& c2, const glm::vec2& p) {
        if (m_data.empty()) return moveTo(p);
        const glm::vec2 start = m_data.back();
        constexpr int segments = 24;
        for (int i = 1; i <= segments; ++i) {
            const float t = static_cast<float>(i) / static_cast<float>(segments);
            glm::vec2 q = std::powf(1 - t, 3) * start +
                          3 * std::powf(1 - t, 2) * t * c1 +
                          3 * (1 - t) * t * t * c2 +
                          t * t * t * p;
            m_data.push_back(q);
        }
        return *this;
    }

    Path& Path::arcTo(const glm::vec2& center, const float radius, const float startAngle, const float endAngle, const bool ccw) {
        constexpr int segments = 32;
        float delta = endAngle - startAngle;
        if (ccw && delta > 0) delta -= glm::two_pi<float>();
        if (!ccw && delta < 0) delta += glm::two_pi<float>();

        for (int i = 0; i <= segments; ++i) {
            const float t = static_cast<float>(i) / segments;
            const float angle = startAngle + delta * t;
            glm::vec2 p = center + glm::vec2(std::cos(angle), std::sin(angle)) * radius;
            m_data.push_back(p);
        }
        return *this;
    }

    Path& Path::close() {
        if (!m_data.empty()) {
            m_data.push_back(m_data.front());
            m_closed = true;
        }
        return *this;
    }

    Path& Path::clear() {
        m_data.clear();
        m_closed = false;
        return *this;
    }

    Path& Path::translate(const glm::vec2& offset) {
        for (auto& p : m_data) p += offset;
        return *this;
    }

    Path& Path::scale(const glm::vec2& s) {
        for (auto& p : m_data) p *= s;
        return *this;
    }

    Path& Path::rotate(const float radians, const glm::vec2& origin) {
        for (auto& p : m_data)
            p = origin + glm::rotate(p - origin, radians);
        return *this;
    }

    glm::vec2 Path::boundsMin() const {
        if (m_data.empty()) return {};
        glm::vec2 min = m_data[0];
        for (auto& p : m_data) min = glm::min(min, p);
        return min;
    }

    glm::vec2 Path::boundsMax() const {
        if (m_data.empty()) return {};
        glm::vec2 max = m_data[0];
        for (auto& p : m_data) max = glm::max(max, p);
        return max;
    }

    glm::vec2 Path::center() const {
        return (boundsMin() + boundsMax()) * 0.5f;
    }

    float Path::length() const {
        if (m_data.size() < 2) return 0.0f;
        float total = 0.0f;
        for (size_t i = 1; i < m_data.size(); ++i)
            total += glm::length(m_data[i] - m_data[i - 1]);
        return total;
    }

    glm::vec2 Path::positionAt(float t) const {
        if (m_data.empty()) return glm::vec2(0);
        if (m_data.size() == 1) return m_data.front();

        t = std::clamp(t, 0.0f, 1.0f);
        const float total = length();
        const float target = total * t;
        float accumulated = 0.0f;

        for (size_t i = 1; i < m_data.size(); ++i) {
            glm::vec2 a = m_data[i - 1];
            glm::vec2 b = m_data[i];
            const float segLen = glm::length(b - a);
            if (accumulated + segLen >= target) {
                const float localT = (target - accumulated) / segLen;
                return glm::mix(a, b, localT);
            }
            accumulated += segLen;
        }

        return m_data.back();
    }

    glm::vec2 Path::directionAt(float t) const {
        if (m_data.size() < 2) return {1, 0};

        t = std::clamp(t, 0.0f, 1.0f);
        const float total = length();
        const float target = total * t;
        float accumulated = 0.0f;

        for (size_t i = 1; i < m_data.size(); ++i) {
            glm::vec2 a = m_data[i - 1];
            glm::vec2 b = m_data[i];
            const float segLen = glm::length(b - a);
            if (accumulated + segLen >= target)
                return glm::normalize(b - a);
            accumulated += segLen;
        }

        return glm::normalize(m_data.back() - m_data[m_data.size() - 2]);
    }

    Path Path::line(const glm::vec2& a, const glm::vec2& b) {
        Path p;
        p.moveTo(a)
         .lineTo(b);
        return p;
    }

    Path Path::rectangle(const glm::vec2& pos, const glm::vec2& size) {
        Path p;
        p.moveTo(pos)
         .lineTo(pos + glm::vec2(size.x, 0))
         .lineTo(pos + size)
         .lineTo(pos + glm::vec2(0, size.y))
         .close();
        return p;
    }

    Path Path::roundedRect(const glm::vec2& pos, const glm::vec2& size, const float radius, const int cornerSegments) {
        return roundedRect(pos, size, glm::vec4{radius}, cornerSegments);
    }

    Path Path::roundedRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& radius, const int cornerSegments) {
        return roundedRect(pos, size, glm::vec4{radius.x,radius.x,radius.y,radius.y}, cornerSegments);
    }

    Path Path::roundedRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& radius, const int cornerSegments) {
            Path p;
            const float w = size.x;
            const float h = size.y;

            const float maxX = w * 0.5f;
            const float maxY = h * 0.5f;

            const glm::vec4 radii = {
                std::min(radius.x, std::min(maxX, maxY)),
                std::min(radius.y, std::min(maxX, maxY)),
                std::min(radius.z, std::min(maxX, maxY)),
                std::min(radius.w, std::min(maxX, maxY))
            };

            const glm::vec2 tl = pos + glm::vec2(radii.x, radii.x);
            const glm::vec2 tr = pos + glm::vec2(w - radii.y, radii.y);
            const glm::vec2 br = pos + glm::vec2(w - radii.z, h - radii.z);
            const glm::vec2 bl = pos + glm::vec2(radii.w, h - radii.w);

            auto arc = [&](const glm::vec2& c, const float r, const float start, const float end) {
                for (int i = 0; i <= cornerSegments; ++i) {
                    const float t = static_cast<float>(i) / static_cast<float>(cornerSegments);
                    const float a = start + (end - start) * t;
                    glm::vec2 pt = c + glm::vec2(std::cos(a), std::sin(a)) * r;
                    if (p.empty()) p.moveTo(pt); else p.lineTo(pt);
                }
            };

            arc(tr, radii.y, glm::radians(-90.f), glm::radians(0.f));
            arc(br, radii.z, glm::radians(0.f), glm::radians(90.f));
            arc(bl, radii.w, glm::radians(90.f), glm::radians(180.f));
            arc(tl, radii.x, glm::radians(180.f), glm::radians(270.f));

            p.close();
            return p;
    }

    Path Path::circle(const glm::vec2& center, const float radius, const int segments) {
        Path p;
        const float step = glm::two_pi<float>() / static_cast<float>(segments);
        for (int i = 0; i <= segments; ++i) {
            const float a = static_cast<float>(i) * step;
            glm::vec2 pt = center + glm::vec2(std::cos(a), std::sin(a)) * radius;
            if (i == 0) p.moveTo(pt); else p.lineTo(pt);
        }
        p.close();
        return p;
    }

    Path Path::ellipse(const glm::vec2& center, const glm::vec2& radii, const int segments) {
        Path p;
        const float step = glm::two_pi<float>() / static_cast<float>(segments);
        for (int i = 0; i <= segments; ++i) {
            const float a = static_cast<float>(i) * step;
            glm::vec2 pt = center + glm::vec2(std::cos(a), std::sin(a)) * radii;
            if (i == 0) p.moveTo(pt); else p.lineTo(pt);
        }
        p.close();
        return p;
    }

}