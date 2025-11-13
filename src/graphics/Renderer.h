#ifndef CIRCUITS_RENDERER_H
#define CIRCUITS_RENDERER_H

#include "Color.h"
#include "Path.h"
#include "Shader.h"
#include "Texture.h"

namespace circuits {

    enum class StrokeCap {
        Butt,
        Round,
        Square
    };

    enum class StrokeJoint {
        Miter,
        Bevel,
        Round
    };

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void load();
        void unload();

        void resize(const glm::ivec2& size);

        void begin();
        void end();

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

    private:

        struct State {
            glm::vec4 fillColor   = {1, 1, 1, 1};
            glm::vec4 strokeColor = {0, 0, 0, 1};
            float strokeWidth     = 1.0f;
            StrokeCap cap         = StrokeCap::Butt;
            StrokeJoint joint     = StrokeJoint::Bevel;
            Texture fillTexture   = {};
        };

        Path m_path;
        Shader m_shader;
        glm::mat4 m_projection;
    };

}

#endif //CIRCUITS_RENDERER_H