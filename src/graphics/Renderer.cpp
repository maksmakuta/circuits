#include "Renderer.h"

#include <optional>
#include <glm/gtc/matrix_transform.hpp>

namespace circuits {

    constexpr auto miterMinAngle = 0.349066;
    constexpr auto roundMinAngle = 0.174533;

    Renderer::Renderer() = default;
    Renderer::~Renderer() = default;

    void Renderer::load() {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

        Vertex::setupAttributes();

        m_shader.loadDefault();
        m_states.push({});
    }

    void Renderer::unload() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        m_shader.unload();
        m_states.pop();
    }

    void Renderer::resize(const glm::ivec2& size) {
        const auto s = glm::vec2(size);
        m_projection = glm::ortho(0.0f, s.x, s.y,0.f);
        m_shader.use();
        m_shader.set("proj", m_projection);
    }

    void Renderer::begin(){
        m_vertices.clear();
    }

    void Renderer::end(){
        flush();
    }

    void Renderer::flush(){
        if (m_vertices.empty()) return;

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<long>(m_vertices.size() * sizeof(Vertex)), m_vertices.data(), GL_DYNAMIC_DRAW);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertices.size()));

        m_vertices.clear();
    }

    void Renderer::newPath() {
        m_path.clear();
    }

    void Renderer::setColor(const Color& c){
        m_states.top().color = c;
    }

    void Renderer::setTexture(const Texture& t, int slot){
        m_states.top().texture = t;
    }

    void Renderer::setThickness(const float thickness){
        m_states.top().width = thickness;
    }

    void Renderer::setStrokeCap(const StrokeCap c){
        m_states.top().cap = c;
    }

    void Renderer::setStrokeJoint(const StrokeJoint j){
        m_states.top().joint = j;
    }

    void Renderer::moveTo(const glm::vec2& point) {
        m_path.moveTo(point);
    }

    void Renderer::lineTo(const glm::vec2& point) {
        m_path.lineTo(point);
    }

    void Renderer::quadTo(const glm::vec2& c, const glm::vec2& p) {
        m_path.quadTo(c, p);
    }

    void Renderer::cubicTo(const glm::vec2& c1, const glm::vec2& c2, const glm::vec2& p) {
        m_path.cubicTo(c1, c2, p);
    }

    void Renderer::arcTo(const glm::vec2& center, const float radius, const float startAngle, const float endAngle, const bool ccw) {
        m_path.arcTo(center, radius, startAngle, endAngle, ccw);
    }

    void Renderer::closePath() {
        m_path.close();
    }

    void Renderer::path(const Path& p) {
        m_path = p;
    }

    void Renderer::line(const glm::vec2& a, const glm::vec2& b) {
        m_path = Path::line(a, b);
    }

    void Renderer::rect(const glm::vec2& pos, const glm::vec2& size) {
        m_path = Path::rectangle(pos,size);
    }

    void Renderer::rect(const glm::vec2& pos, const glm::vec2& size, const float radius) {
        m_path = Path::roundedRect(pos,size,radius);
    }

    void Renderer::rect(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& radius) {
        m_path = Path::roundedRect(pos,size,radius);
    }

    void Renderer::rect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& radius) {
        m_path = Path::roundedRect(pos,size,radius);
    }

    void Renderer::circle(const glm::vec2& pos, const float radius) {
        m_path = Path::circle(pos,radius);
    }

    void Renderer::ellipse(const glm::vec2& pos, const glm::vec2& size) {
        m_path = Path::ellipse(pos,size);
    }

    void Renderer::clear(const Color& c) {
        glClearColor(c.r(), c.g(), c.b(), c.a());
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::fill(){
        fill(m_states.top().color);
    }

    void Renderer::fill(const Color& c){
        if (m_path.size() < 3) {
            return;
        }
        const auto base = m_path.points().front();
        for (auto i = 1; i < m_path.size(); i++) {
            m_vertices.emplace_back(base,c.asVec4());
            m_vertices.emplace_back(m_path.points()[i-1],c.asVec4());
            m_vertices.emplace_back(m_path.points()[i],c.asVec4());
        }
    }

    void Renderer::fill(const Texture& t){
        fill(
            t,
            m_states.top().uv,
            m_states.top().color
        );
    }

    void Renderer::fill(const Texture& t, const Color& c){
        fill(
            t,
            m_states.top().uv,
            c
        );
    }

    void Renderer::fill(const Texture& t, const glm::vec4& u){
        fill(
            t,
            u,
            m_states.top().color
        );
    }

    void Renderer::fill(const Texture&, const glm::vec4&, const Color&){
        //TODO(implement fill algorithm: texture fill)
    }

    void Renderer::stroke(){
        stroke(
            m_states.top().color,
            m_states.top().width
        );
    }

    void Renderer::stroke(const Color& c){
        stroke(
            c,
            m_states.top().width
        );
    }

    void Renderer::stroke(const float w){
        stroke(
            m_states.top().color,
            w
        );
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

            vertices.emplace_back(startPoint,color.asVec4());
            vertices.emplace_back(endPoint,color.asVec4());
            vertices.emplace_back(connectTo,color.asVec4());

            startPoint = endPoint;
        }

    }

    void createJoint(std::vector<Vertex>& vertices,const Segment &segment1, const Segment&segment2,
        StrokeJoint jointStyle, glm::vec2 &end1, glm::vec2 &end2,glm::vec2 &nextStart1, glm::vec2 &nextStart2,
        const bool allowOverlap, const Color& color) {

        const auto dir1 = segment1.center.direction();
        const auto dir2 = segment2.center.direction();
        const auto angle = getAngle(dir1, dir2);

        auto wrappedAngle = angle;
        if (wrappedAngle > glm::pi<float>() / 2) {
            wrappedAngle = glm::pi<float>() - wrappedAngle;
        }

        if (jointStyle == StrokeJoint::Miter && wrappedAngle < miterMinAngle) {
            jointStyle = StrokeJoint::Bevel;
        }

        if (jointStyle == StrokeJoint::Miter) {
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

            if (jointStyle == StrokeJoint::Bevel) {
                vertices.emplace_back(outer1->b, color.asVec4());
                vertices.emplace_back(outer2->a, color.asVec4());
                vertices.emplace_back(innerSec, color.asVec4());
            } else if (jointStyle == StrokeJoint::Round) {
                createTriangleFan(vertices, innerSec, segment1.center.b, outer1->b, outer2->a, clockwise, color);
            } else {
                assert(false);
            }
        }
    }

    void Renderer::stroke(const Color& color, const float w){
        const auto& path = m_path;
        const auto& points = path.points();
        const auto& state = m_states.top();
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

        if (state.cap == StrokeCap::Square) {
            pathStart1 -= firstSegment.edge1.direction() * thickness;
            pathStart2 -= firstSegment.edge2.direction() * thickness;
            pathEnd1 += lastSegment.edge1.direction() * thickness;
            pathEnd2 += lastSegment.edge2.direction() * thickness;

        } else if (state.cap == StrokeCap::Round) {
            createTriangleFan(m_vertices, firstSegment.center.a, firstSegment.center.a,
                              firstSegment.edge1.a, firstSegment.edge2.a, false, color);
            createTriangleFan(m_vertices, lastSegment.center.b, lastSegment.center.b,
                              lastSegment.edge1.b, lastSegment.edge2.b, true, color);

        } else if (path.isClosed()) {
            createJoint(m_vertices, lastSegment, firstSegment,
                state.joint,pathEnd1, pathEnd2,
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
                 createJoint(m_vertices, segment, segments[i + 1], state.joint,
                             end1, end2, nextStart1, nextStart2, false, color);
            }

            m_vertices.emplace_back(start1,color.asVec4());
            m_vertices.emplace_back(start2,color.asVec4());
            m_vertices.emplace_back(end1,color.asVec4());

            m_vertices.emplace_back(end1, color.asVec4());
            m_vertices.emplace_back(start2, color.asVec4());
            m_vertices.emplace_back(end2, color.asVec4());

            start1 = nextStart1;
            start2 = nextStart2;
        }

    }


}
