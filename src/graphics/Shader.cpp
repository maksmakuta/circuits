#include "Shader.h"

namespace circuits {

    void Shader::unload() {
        if (m_program)
            glDeleteProgram(m_program);
        m_program = 0;
    }

    bool Shader::load(const std::string& vertexSrc, const std::string& fragmentSrc) {
        const GLuint vert = compile(GL_VERTEX_SHADER, vertexSrc);
        const GLuint frag = compile(GL_FRAGMENT_SHADER, fragmentSrc);
        if (!vert || !frag)
            return false;

        m_program = glCreateProgram();
        glAttachShader(m_program, vert);
        glAttachShader(m_program, frag);
        glLinkProgram(m_program);

        GLint success = 0;
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        glDeleteShader(vert);
        glDeleteShader(frag);

        if (!success) {
            char info[512];
            glGetProgramInfoLog(m_program, 512, nullptr, info);
            std::fprintf(stderr, "Shader link error:\n%s\n", info);
            glDeleteProgram(m_program);
            m_program = 0;
            return false;
        }
        return true;
    }

    void Shader::use() const {
        glUseProgram(m_program);
    }

    GLuint Shader::compile(const GLenum type, const std::string& src) {
        const GLuint shader = glCreateShader(type);
        const char* csrc = src.c_str();
        glShaderSource(shader, 1, &csrc, nullptr);
        glCompileShader(shader);

        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info[512];
            glGetShaderInfoLog(shader, 512, nullptr, info);
            std::fprintf(stderr, "Shader compile error:\n%s\n", info);
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }

    void Shader::set(const std::string& name, const int value) const {
        glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
    }

    void Shader::set(const std::string& name, const float value) const {
        glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
    }

    void Shader::set(const std::string& name, const glm::vec2& v) const {
        glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &v.x);
    }

    void Shader::set(const std::string& name, const glm::vec3& v) const {
        glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &v.x);
    }

    void Shader::set(const std::string& name, const glm::vec4& v) const {
        glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &v.x);
    }

    void Shader::set(const std::string& name, const glm::mat3& m) const {
        glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &m[0][0]);
    }

    void Shader::set(const std::string& name, const glm::mat4& m) const {
        glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &m[0][0]);
    }

}