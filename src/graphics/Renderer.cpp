#include "Renderer.h"

#include <Polyline2D.h>
#include <glm/gtc/matrix_transform.hpp>

namespace circuits {

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
        m_states.top().color1 = c;
    }

    void Renderer::setGradientType(const bool is_linear) {
        m_states.top().is_linear = is_linear;
    }

    void Renderer::setGradientColors(const Color& c1, const Color& c2) {
        m_states.top().color2 = c2;
        m_states.top().color1 = c1;
    }

    void Renderer::setGradientAngle(const float angle) {
        m_states.top().angle = angle;
    }

    void Renderer::setGradientCenter(const glm::vec2& center) {
        m_states.top().center = center;
    }

    void Renderer::setColorGradient(const Color& c1,const Color& c2, const glm::vec2& c, float a){
        m_states.top().color2 = c2;
        m_states.top().color1 = c1;
        m_states.top().angle = a;
        m_states.top().center = c;
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
        fill(m_states.top().color1);
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

    void Renderer::fill(const Color&, const Color&, float){
        //TODO(implement fill algorithm: gradient fill)
    }

    void Renderer::fill(const Texture& t){
        fill(
            t,
            m_states.top().uv,
            m_states.top().color1
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
            m_states.top().color1
        );
    }

    void Renderer::fill(const Texture&, const glm::vec4&, const Color&){
        //TODO(implement fill algorithm: texture fill)
    }

    void Renderer::stroke(){
        stroke(
            m_states.top().color1,
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
            m_states.top().color1,
            w
        );
    }

    void Renderer::stroke(const Color& color, const float w){
        const auto& path = m_path.points();
        const auto& state = m_states.top();

    }


}
