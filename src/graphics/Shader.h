#ifndef CIRCUITS_SHADER_H
#define CIRCUITS_SHADER_H

#include <string>
#include <glm/glm.hpp>

#include "glad/gl.h"

namespace circuits {

    class Shader {
    public:
        Shader() = default;

        bool loadDefault();
        bool load(const std::string& vertexSrc, const std::string& fragmentSrc);
        void unload();

        void use() const;
        [[nodiscard]] GLuint id() const { return m_program; }

        void set(const std::string& name, int value) const;
        void set(const std::string& name, float value) const;
        void set(const std::string& name, const glm::vec2& v) const;
        void set(const std::string& name, const glm::vec3& v) const;
        void set(const std::string& name, const glm::vec4& v) const;
        void set(const std::string& name, const glm::mat3& m) const;
        void set(const std::string& name, const glm::mat4& m) const;

    private:
        GLuint m_program = 0;

        static GLuint compile(GLenum type, const std::string& src);
    };

}


#endif //CIRCUITS_SHADER_H