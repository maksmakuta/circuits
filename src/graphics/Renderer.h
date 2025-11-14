#ifndef CIRCUITS_RENDERER_H
#define CIRCUITS_RENDERER_H

#include <stack>

#include "Color.h"
#include "Font.h"
#include "Path.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

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
        void flush();

        void setColor(const Color&);
        void setColorGradient(const Color&,const Color&, float);
        void setTexture(const Texture&);
        void setThickness(float thickness);
        void setStrokeCap(StrokeCap);
        void setStrokeJoint(StrokeJoint);

        void newPath();
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
        void fill(const Color&, const Color&, float);
        void fill(const Texture&);
        void fill(const Texture&, const Color&);
        void fill(const Texture&, const glm::vec4&);
        void fill(const Texture&, const glm::vec4&, const Color&);

        void stroke();
        void stroke(const Color&);
        void stroke(float);
        void stroke(const Color&, float = 1.f);

    private:

        struct State {
            Color color1        = {0, 0, 0, 1};
            Color color2        = {0, 0, 0, 1};
            float width         = 1.0f;
            float angle         = 0;
            Texture texture     = {};
            glm::vec4 uv        = {0,0,1,1};
            StrokeCap cap       = StrokeCap::Butt;
            StrokeJoint joint   = StrokeJoint::Bevel;
            Font font           = {};
        };

        GLuint m_vao = 0;
        GLuint m_vbo = 0;
        GLuint m_ibo = 0;
        Path m_path;
        Shader m_shader;
        glm::mat4 m_projection{1.f};
        std::stack<State> m_states;
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indexes;
    };

}

#endif //CIRCUITS_RENDERER_H