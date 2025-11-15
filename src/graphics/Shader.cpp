#include "Shader.h"

namespace circuits {

    const auto DEFAULT_SHADER_V = R"(
        #version 460 core

        layout(location = 0) in vec2 pos;
        layout(location = 1) in vec2 uv;
        layout(location = 2) in vec4 col;
        layout(location = 3) in uint dat;

        uniform mat4 proj;

        out vec2 v_pos;
        out vec2 v_uv;
        out vec4 v_col;
        flat out uint v_tex;
        flat out uint v_op;

        void main(){
            v_pos = pos;
            v_uv = uv;
            v_col = col;
            v_op = dat & 0xFu;
            v_tex = (dat >> 4) & 0xFu;
            gl_Position = proj * vec4(pos, 0.0, 1.0);
        }
    )";

    const auto DEFAULT_SHADER_F = R"(
        #version 460 core

        in vec2 v_pos;
        in vec2 v_uv;
        in vec4 v_col;
        flat in uint v_tex;
        flat in uint v_op;

        uniform sampler2D images[16];
        uniform vec4 g_colorB;
        uniform vec2 g_center;
        uniform float g_angle;
        uniform float g_radius;

        out vec4 f_col;

        void main(){
            if(v_op == 0){
                f_col = v_col;
            } else if(v_op == 1){
                f_col = texture(images[v_tex],v_uv);
            } else if(v_op == 2){
                vec4 mult = v_col * texture(images[v_tex],v_uv);
                f_col = vec4(mult.rgb, v_col.a);
            } else if(v_op == 3){
                f_col = vec4(v_col.rgb, v_col.a * texture(images[v_tex],v_uv).r);
            } else if(v_op == 4){
                vec2 dir = vec2(cos(g_angle), sin(g_angle));
                vec2 d = v_pos - g_center;
                float t = dot(d, dir);
                t = (t / g_radius) * 0.5 + 0.5;
                t = clamp(t, 0.0, 1.0);
                f_col = mix(v_col, g_colorB, t);
            } else if(v_op == 5){
                float dist = length(v_pos - g_center);
                float t = dist / g_radius;
                t = clamp(t, 0.0, 1.0);
                f_col = mix(v_col, g_colorB, t);
            }else{
                discard;
            }
        }
    )";

    void Shader::unload() {
        if (m_program)
            glDeleteProgram(m_program);
        m_program = 0;
    }

    bool Shader::loadDefault() {
        return load(DEFAULT_SHADER_V,DEFAULT_SHADER_F);
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