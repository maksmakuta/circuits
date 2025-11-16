#ifndef CIRCUITS_RENDERER_H
#define CIRCUITS_RENDERER_H

#include <string>
#include <glm/mat4x4.hpp>

#include "Color.h"
#include "Font.h"
#include "Path.h"
#include "Texture.h"
#include "Vertex.h"

namespace circuits {

    enum class Cap {
        Butt,
        Round,
        Square
    };

    enum class Joint {
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

        void begin();
        void resize(const glm::vec2&);
        void flush();
        void end();

        void newPath();
        void moveTo(const glm::vec2&);
        void lineTo(const glm::vec2&);
        void quadTo(const glm::vec2&, const glm::vec2&);
        void cubicTo(const glm::vec2&, const glm::vec2& , const glm::vec2& );
        void arcTo(const glm::vec2&, const glm::vec2&, float, float, bool = false);
        void close();

        void translate(const glm::vec2&);
        void scale(float);
        void scale(const glm::vec2&);
        void rotate(float);
        void rotate(float, const glm::vec2&);

        void setFont(const Font&);
        void setCap(const Cap&);
        void setJoint(const Joint&);

        void point(const glm::vec2&);
        void line(const glm::vec2&,const glm::vec2&);
        void triangle(const glm::vec2&,const glm::vec2&,const glm::vec2&);
        void rect(const glm::vec2&,const glm::vec2&);
        void rect(const glm::vec2&,const glm::vec2&,float);
        void rect(const glm::vec2&,const glm::vec2&,const glm::vec2&);
        void rect(const glm::vec2&,const glm::vec2&,const glm::vec4&);
        void circle(const glm::vec2&, float, int = 32);
        void ellipse(const glm::vec2&, const glm::vec2&, int = 32);
        void arc(const glm::vec2&, const glm::vec2&, float, float, int = 32);
        void pie(const glm::vec2&, const glm::vec2&, float, float, int = 32);
        void path(const Path&);

        void fill(const Color&);
        void fill(const Texture&, const glm::vec2&, const glm::vec2&);
        void stroke(const Color&, float);
        void text(const std::string&, const glm::vec2&);
    private:
        glm::uint m_vao{0};
        glm::uint m_vbo{0};
        Path m_path;
        Cap m_cap = Cap::Butt;
        Joint m_joint = Joint::Bevel;
        std::vector<Vertex> m_vertices;
        glm::mat4 m_projection{1.f};
    };

}

#endif //CIRCUITS_RENDERER_H