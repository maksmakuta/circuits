#ifndef CIRCUITS_TEXTURE_H
#define CIRCUITS_TEXTURE_H

#include <string>
#include <glm/glm.hpp>

#include "glad/gl.h"

namespace circuits {

    class Texture {
    public:
        Texture() = default;
        ~Texture() { unload(); }

        bool load(const std::string& path);
        void unload();

        void bind(unsigned int slot = 0) const;

        [[nodiscard]] GLuint id() const { return m_id; }
        [[nodiscard]] glm::ivec2 size() const { return m_size; }

    private:
        GLuint m_id = 0;
        glm::ivec2 m_size{0};
    };

}

#endif //CIRCUITS_TEXTURE_H