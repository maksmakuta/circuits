#include "Renderer.h"

namespace circuits {

    Renderer::Renderer(){}
    Renderer::~Renderer(){}

    void Renderer::load(){}
    void Renderer::unload(){}

    void Renderer::resize(const glm::ivec2& size) {

    }

    void Renderer::begin(){

    }

    void Renderer::end(){

    }

    void beginPath();
    void endPath();

    void setColor(const Color&);
    void setTexture(Texture);
    void setThickness(float thickness);
    void setStrokeCap(StrokeCap);
    void setStrokeJoint(StrokeJoint);

    void moveTo(const glm::vec2& point);
    void lineTo(const glm::vec2& point);
    void quadTo(const glm::vec2& c, const glm::vec2& p);
    void cubicTo(const glm::vec2& c1, const glm::vec2& c2, const glm::vec2& p);
    void arcTo(const glm::vec2& center, float radius, float startAngle, float endAngle, bool ccw = false);
    void closePath();

    void line(const glm::vec2& a, const glm::vec2& b);
    void rect(const glm::vec2& pos, const glm::vec2& size);
    void rect(const glm::vec2& pos, const glm::vec2& size, float radius);
    void rect(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& radius);
    void rect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& radius);
    void circle(const glm::vec2& pos, float radius);
    void ellipse(const glm::vec2& pos, const glm::vec2& size);

    void fill();
    void fill(const Color&);
    void fill(const Texture&);
    void stroke();
    void stroke(const Color&, float thickness = 1.f);

}