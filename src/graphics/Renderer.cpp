#include "Renderer.h"

#include <iostream>
#include <optional>
#include <ostream>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/gl.h"

namespace circuits {

    constexpr auto miterMinAngle = 0.349066;
    constexpr auto roundMinAngle = 0.174533;

    void clear(const glm::uint c) {
        clear(Color(c));
    }

    void clear(const Color& c) {
        clear(c.asVec4());
    }

    void clear(const glm::vec4& c) {
        clear(glm::vec3{c.r,c.g,c.b});
    }

    void clear(const glm::vec3& c) {
        glClearColor(c.r, c.g, c.b, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    Renderer::Renderer() = default;
    Renderer::~Renderer() = default;

    void Renderer::load() {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,pos)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,uv)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,col)));

        m_shader.loadDefault();
        m_shader.use();
    }

    void Renderer::unload() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        m_shader.unload();
        m_vao = m_vbo = 0;
    }

    void Renderer::begin() {
        m_vertices.clear();
    }

    void Renderer::end() const {
        flush();
    }

    void Renderer::flush() const {
        if (m_vertices.empty()) return;

        m_shader.use();
        m_shader.set("op",m_paint);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<long>(m_vertices.size() * sizeof(Vertex)), m_vertices.data(), GL_DYNAMIC_DRAW);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertices.size()));

    }

    void Renderer::resize(const glm::vec2& s) {
        m_projection = glm::ortho(0.f, s.x, s.y, 0.f);
        m_shader.set("proj",m_projection);
        const auto is = glm::ivec2(s);
        glViewport(0,0,is.x,is.y);
    }

    void Renderer::newPath() {
        m_path.clear();
    }

    void Renderer::moveTo(const glm::vec2& p) {
        m_path.moveTo(p);
    }

    void Renderer::lineTo(const glm::vec2& p) {
        m_path.lineTo(p);
    }

    void Renderer::quadTo(const glm::vec2& c, const glm::vec2& p) {
        m_path.quadTo(c, p);
    }

    void Renderer::cubicTo(const glm::vec2& c1, const glm::vec2& c2, const glm::vec2& p) {
        m_path.cubicTo(c1, c2, p);
    }

    void Renderer::arcTo(const glm::vec2& c, const glm::vec2& r, const float begin, const float end, const bool ccw) {
        m_path.arcTo(c,r,begin,end,ccw);
    }

    void Renderer::close() {
        m_path.close();
    }

    void Renderer::translate(const glm::vec2& p){
        m_path.translate(p);
    }

    void Renderer::scale(const float s){
        m_path.scale(s);
    }

    void Renderer::scale(const glm::vec2& s){
        m_path.scale(s);
    }

    void Renderer::rotate(const float a){
        m_path.rotate(a);
    }

    void Renderer::rotate(const float a, const glm::vec2& p){
        m_path.rotate(a, p);
    }

    void Renderer::point(const glm::vec2& p) {
        path(
            Path()
            .moveTo(p)
        );
    }

    void Renderer::line(const glm::vec2& a,const glm::vec2& b) {
        path(
            Path()
            .moveTo(a)
            .lineTo(b)
        );
    }

    void Renderer::triangle(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c) {
        path(
            Path()
            .moveTo(a)
            .lineTo(b)
            .lineTo(c)
            .close()
        );
    }

    void Renderer::rect(const glm::vec2& p,const glm::vec2& s) {
        path(
            Path()
            .moveTo(p)
            .lineTo(p + glm::vec2(s.x,0))
            .lineTo(p + s)
            .lineTo(p + glm::vec2(0,s.y))
            .close()
        );
    }

    void Renderer::rect(const glm::vec2& p,const glm::vec2& s,float r) {
        rect(p,s,glm::vec4(r));
    }

    void Renderer::rect(const glm::vec2& p,const glm::vec2& s,const glm::vec2& r) {
        rect(p,s,glm::vec4(r.x,r.x,r.y,r.y));
    }

    void Renderer::rect(const glm::vec2& pos,const glm::vec2& s,const glm::vec4& r) {
        constexpr auto cornerSegments = 8;
        Path p;
        const auto max = s * 0.5f;

        const glm::vec4 radii = {
            std::min(r.x, std::min(max.x, max.y)),
            std::min(r.y, std::min(max.x, max.y)),
            std::min(r.z, std::min(max.x, max.y)),
            std::min(r.w, std::min(max.x, max.y))
        };

        const glm::vec2 tl = pos + glm::vec2(radii.x, radii.x);
        const glm::vec2 tr = pos + glm::vec2(s.x - radii.y, radii.y);
        const glm::vec2 br = pos + glm::vec2(s.x - radii.z, s.y - radii.z);
        const glm::vec2 bl = pos + glm::vec2(radii.w, s.y - radii.w);

        auto arc = [&](const glm::vec2& c, const float rs, const float start, const float end) {
            for (int i = 0; i <= cornerSegments; ++i) {
                const float t = static_cast<float>(i) / static_cast<float>(cornerSegments);
                const float a = start + (end - start) * t;
                glm::vec2 pt = c + glm::vec2(std::cos(a), std::sin(a)) * rs;
                if (p.empty()) p.moveTo(pt); else p.lineTo(pt);
            }
        };

        arc(tr, radii.y, glm::radians(-90.f), glm::radians(0.f));
        arc(br, radii.z, glm::radians(0.f), glm::radians(90.f));
        arc(bl, radii.w, glm::radians(90.f), glm::radians(180.f));
        arc(tl, radii.x, glm::radians(180.f), glm::radians(270.f));

        p.close();
        path(p);
    }

    void Renderer::circle(const glm::vec2& c, const float r, const int segments) {
        auto p = Path();
        const float step = glm::two_pi<float>() / static_cast<float>(segments);
        for (int i = 0; i <= segments; ++i) {
            const float a = static_cast<float>(i) * step;
            glm::vec2 pt = c + glm::vec2(std::cos(a), std::sin(a)) * r;
            if (i == 0) p.moveTo(pt); else p.lineTo(pt);
        }
        p.close();
        path(p);
    }

    void Renderer::ellipse(const glm::vec2& c, const glm::vec2& r, const int segments) {
        auto p = Path();
        const float step = glm::two_pi<float>() / static_cast<float>(segments);
        for (int i = 0; i <= segments; ++i) {
            const float a = static_cast<float>(i) * step;
            glm::vec2 pt = c + glm::vec2(std::cos(a), std::sin(a)) * r;
            if (i == 0) p.moveTo(pt); else p.lineTo(pt);
        }
        p.close();
        path(p);
    }

    void Renderer::arc(const glm::vec2& c, const glm::vec2& r, const float a, const float b, const int segments) {
        auto p = Path();
        const float step = (b - a) / static_cast<float>(segments);
        for (int i = 0; i <= segments; ++i) {
            const float d = a + static_cast<float>(i) * step;
            glm::vec2 pt = c + glm::vec2(std::cos(d), std::sin(d)) * r;
            if (i == 0) p.moveTo(pt); else p.lineTo(pt);
        }
        p.close();
        path(p);
    }

    void Renderer::pie(const glm::vec2& c, const glm::vec2& r, const float a, const float b, const int segments) {
        auto p = Path();
        const float step = (b - a) / static_cast<float>(segments);
        p.moveTo(c);
        for (int i = 0; i <= segments; ++i) {
            const float d = a + static_cast<float>(i) * step;
            glm::vec2 pt = c + glm::vec2(std::cos(d), std::sin(d)) * r;
            p.lineTo(pt);
        }
        p.close();
        path(p);
    }

    void Renderer::path(const Path& p) {
        m_path = p;
    }

    void Renderer::fill(const Color& c) {
        setPaint(0);
        if (m_path.size() < 3) {
            std::cerr << "Can't fill empty path!" << std::endl;
            return;
        }

        const auto base = m_path.points().front();
        for (auto i = 1; i < m_path.size(); ++i) {
            m_vertices.emplace_back(base,c);
            m_vertices.emplace_back(m_path.points()[i-1],c);
            m_vertices.emplace_back(m_path.points()[i],c);
        }
    }

    void Renderer::fill(const Texture&, const glm::vec2&, const glm::vec2&) {
        setPaint(1);
    }

    void Renderer::text(const std::string&, const glm::vec2&) {
        setPaint(2);
    }

    void Renderer::setFont(const Font&) {

    }

    void Renderer::setCap(const Cap& c) {
        m_cap = c;
    }

    void Renderer::setJoint(const Joint& j) {
        m_joint = j;
    }

    struct Line {
        Line(const glm::vec2& start, const glm::vec2& end): a(start), b(end){}

        Line operator+(const glm::vec2& v) const {
            return {a+v, b+v};
        }

        Line operator-(const glm::vec2& v) const {
            return {a-v, b-v};
        }

        [[nodiscard]] glm::vec2 normal() const {
            auto dir = direction();
            return {-dir.y, dir.x};
        }

        [[nodiscard]] glm::vec2 direction(const bool n = true) const {
            const auto vec = b - a;
            return n ? glm::normalize(vec) : vec;
        }

        glm::vec2 a,b;
    };

    static float cross(const glm::vec2 &a, const glm::vec2 &b) {
        return a.x * b.y - a.y * b.x;
    }

    std::optional<glm::vec2> intersection(const Line& a, const Line& b, const bool inf = false) {
        const auto r = a.direction(false);
        const auto s = b.direction(false);
        const auto originDist = b.a - a.a;
        const auto uNumerator = cross(originDist, r);
        const auto denominator = cross(r, s);
        if (std::abs(denominator) < 0.0001f) {
            return std::nullopt;
        }
        const auto u = uNumerator / denominator;
        const auto t = cross(originDist, s) / denominator;
        if (!inf && (t < 0 || t > 1 || u < 0 || u > 1)) {
            return std::nullopt;
        }
        return a.a + r * t;
    }

    struct Segment {
        Segment(const Line& l, const float t) : center(l),
            edge1(l + center.normal() * t) ,edge2(l - center.normal() * t){}
        Line center, edge1, edge2;
    };

    float getAngle(const glm::vec2 &a, const glm::vec2 &b) {
        return std::acos(glm::dot(a, b) / (glm::length(a) * glm::length(b)));
    }

    void createTriangleFan(std::vector<Vertex>& vertices, const glm::vec2& connectTo, const glm::vec2& origin,
        const glm::vec2& start, const glm::vec2& end, const bool clockwise, const Color& color) {

        const auto point1 = start - origin;
        const auto point2 = end - origin;
        auto angle1 = atan2(point1.y, point1.x);
        auto angle2 = atan2(point2.y, point2.x);
        if (clockwise) {
            if (angle2 > angle1) {
                angle2 = angle2 - glm::two_pi<float>();
            }
        } else {
            if (angle1 > angle2) {
                angle1 = angle1 - glm::two_pi<float>();
            }
        }

        const auto jointAngle = angle2 - angle1;
        const auto numTriangles = std::max(1, static_cast<int>(std::floor(std::abs(jointAngle) / roundMinAngle)));
        const auto triAngle = jointAngle / numTriangles;

        glm::vec2 startPoint = start;
        glm::vec2 endPoint;
        for (int t = 0; t < numTriangles; t++) {
            if (t + 1 == numTriangles) {
                endPoint = end;
            } else {
                const auto rot = static_cast<float>((t + 1) * triAngle);

                endPoint.x = std::cosf(rot) * point1.x - std::sinf(rot) * point1.y;
                endPoint.y = std::sinf(rot) * point1.x + std::cosf(rot) * point1.y;

                endPoint += origin;
            }

            vertices.emplace_back(startPoint,color);
            vertices.emplace_back(endPoint,color);
            vertices.emplace_back(connectTo,color);

            startPoint = endPoint;
        }

    }

    void createJoint(std::vector<Vertex>& vertices,const Segment &segment1, const Segment& segment2,
        Joint jointStyle, glm::vec2 &end1, glm::vec2 &end2,glm::vec2 &nextStart1, glm::vec2 &nextStart2,
        const bool allowOverlap, const Color& color) {

        const auto dir1 = segment1.center.direction();
        const auto dir2 = segment2.center.direction();
        const auto angle = getAngle(dir1, dir2);

        auto wrappedAngle = angle;
        if (wrappedAngle > glm::pi<float>() / 2) {
            wrappedAngle = glm::pi<float>() - wrappedAngle;
        }

        if (jointStyle == Joint::Miter && wrappedAngle < miterMinAngle) {
            jointStyle = Joint::Bevel;
        }

        if (jointStyle == Joint::Miter) {
            const auto sec1 = intersection(segment1.edge1, segment2.edge1, true);
            const auto sec2 = intersection(segment1.edge2, segment2.edge2, true);

            end1 = sec1 ? *sec1 : segment1.edge1.b;
            end2 = sec2 ? *sec2 : segment1.edge2.b;

            nextStart1 = end1;
            nextStart2 = end2;
        } else {
            const auto x1 = dir1.x;
            const auto x2 = dir2.x;
            const auto y1 = dir1.y;
            const auto y2 = dir2.y;

            const auto clockwise = x1 * y2 - x2 * y1 < 0;
            const Line *inner1, *inner2, *outer1, *outer2;

            if (clockwise) {
                outer1 = &segment1.edge1;
                outer2 = &segment2.edge1;
                inner1 = &segment1.edge2;
                inner2 = &segment2.edge2;
            } else {
                outer1 = &segment1.edge2;
                outer2 = &segment2.edge2;
                inner1 = &segment1.edge1;
                inner2 = &segment2.edge1;
            }

            auto innerSecOpt = intersection(*inner1, *inner2, allowOverlap);
            auto innerSec = innerSecOpt ? *innerSecOpt : inner1->b;

            glm::vec2 innerStart;
            if (innerSecOpt) {
                innerStart = innerSec;
            } else if (angle > glm::pi<float>() / 2) {
                innerStart = outer1->b;
            } else {
                innerStart = inner1->b;
            }

            if (clockwise) {
                end1 = outer1->b;
                end2 = innerSec;

                nextStart1 = outer2->a;
                nextStart2 = innerStart;
            } else {
                end1 = innerSec;
                end2 = outer1->b;

                nextStart1 = innerStart;
                nextStart2 = outer2->a;
            }

            if (jointStyle == Joint::Bevel) {
                vertices.emplace_back(outer1->b, color);
                vertices.emplace_back(outer2->a, color);
                vertices.emplace_back(innerSec, color);
            } else if (jointStyle == Joint::Round) {
                createTriangleFan(vertices, innerSec, segment1.center.b, outer1->b, outer2->a, clockwise, color);
            } else {
                assert(false);
            }
        }
    }

    void Renderer::stroke(const Color& color, const float w){
        setPaint(0);
        const auto& path = m_path;
        const auto& points = path.points();
        const auto thickness = w / 2.f;

        std::vector<Segment> segments;
        for (size_t i = 0; i + 1 < points.size(); i++) {
            const auto &point1 = points[i];
            const auto &point2 = points[i + 1];
            if (point1 != point2) {
                segments.emplace_back(Line(point1, point2), thickness);
            }
        }

        if (path.isClosed()) {
            const auto &point1 = points.back();
            const auto &point2 = points.front();
            if (point1 != point2) {
                segments.emplace_back(Line(point1, point2), thickness);
            }
        }

        if (segments.empty()) {
            return;
        }

        glm::vec2 nextStart1{0, 0};
        glm::vec2 nextStart2{0, 0};
        glm::vec2 start1{0, 0};
        glm::vec2 start2{0, 0};
        glm::vec2 end1{0, 0};
        glm::vec2 end2{0, 0};

        auto &firstSegment = segments[0];
        auto &lastSegment = segments[segments.size() - 1];

        auto pathStart1 = firstSegment.edge1.a;
        auto pathStart2 = firstSegment.edge2.a;
        auto pathEnd1 = lastSegment.edge1.b;
        auto pathEnd2 = lastSegment.edge2.b;

        if (m_cap == Cap::Square) {
            pathStart1 -= firstSegment.edge1.direction() * thickness;
            pathStart2 -= firstSegment.edge2.direction() * thickness;
            pathEnd1 += lastSegment.edge1.direction() * thickness;
            pathEnd2 += lastSegment.edge2.direction() * thickness;

        } else if (m_cap == Cap::Round) {
            createTriangleFan(m_vertices, firstSegment.center.a, firstSegment.center.a,
                              firstSegment.edge1.a, firstSegment.edge2.a, false, color);
            createTriangleFan(m_vertices, lastSegment.center.b, lastSegment.center.b,
                              lastSegment.edge1.b, lastSegment.edge2.b, true, color);

        } else if (path.isClosed()) {
            createJoint(m_vertices, lastSegment, firstSegment,
                m_joint,pathEnd1, pathEnd2,
                pathStart1, pathStart2,
                false, color);
        }

        for (size_t i = 0; i < segments.size(); i++) {
            auto &segment = segments[i];

            if (i == 0) {
                start1 = pathStart1;
                start2 = pathStart2;
            }

            if (i + 1 == segments.size()) {
                end1 = pathEnd1;
                end2 = pathEnd2;

            } else {
                 createJoint(m_vertices, segment, segments[i + 1], m_joint,
                             end1, end2, nextStart1, nextStart2, false, color);
            }

            m_vertices.emplace_back(start1,color);
            m_vertices.emplace_back(start2,color);
            m_vertices.emplace_back(end1,color);

            m_vertices.emplace_back(end1, color);
            m_vertices.emplace_back(start2, color);
            m_vertices.emplace_back(end2, color);

            start1 = nextStart1;
            start2 = nextStart2;
        }

    }

    void Renderer::setPaint(const int p) {
        if (m_paint != p) {
            flush();
            m_vertices.clear();
            m_paint = p;
        }
    }


}
