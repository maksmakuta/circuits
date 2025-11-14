#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace circuits {

    Renderer::Renderer() = default;
    Renderer::~Renderer() = default;

    void Renderer::load() {
        //load VAO, VBO, shader
        m_states.push({});
    }

    void Renderer::unload() {
        //unload VAO, VBO, shader
        m_states.pop();
    }

    void Renderer::resize(const glm::ivec2& size) {
        const auto s = glm::vec2(size);
        m_projection = glm::ortho(0.0f, s.x, s.y,0.f);
    }

    void Renderer::begin(){
        m_vertices.clear();
    }

    void Renderer::end(){
        flush();
    }

    void Renderer::flush(){
        //TODO(implement flush algorithm)
    }

    void Renderer::newPath() {
        m_path.clear();
    }

    void Renderer::setColor(const Color& c){
        m_states.top().color1 = c;
    }

    void Renderer::setColorGradient(const Color& c1,const Color& c2, const float angle) {
        m_states.top().color2 = c2;
        m_states.top().color1 = c1;
        m_states.top().angle = angle;
    }

    void Renderer::setTexture(const Texture& t){
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

    void Renderer::fill(){
        fill(m_states.top().color1);
    }

    void Renderer::fill(const Color&){
        //TODO(implement fill algorithm: 1 color fill)
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

    void Renderer::stroke(const Color& c, float w){
        //TODO(implement stroke algorithm)
    }

}
