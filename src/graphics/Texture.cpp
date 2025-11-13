#include "Texture.h"

#include "lodePNG/lodepng.h"

namespace circuits {

    bool Texture::load(const std::string& path) {
        unload();

        std::vector<unsigned char> image;
        unsigned w, h;

        if (const unsigned error = lodepng::decode(image, w, h, path)) {
            std::fprintf(stderr, "Failed to load PNG: %s (%u: %s)\n",
                         path.c_str(), error, lodepng_error_text(error));
            return false;
        }

        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            static_cast<int>(w), static_cast<int>(h),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            image.data()
        );

        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        m_size = {static_cast<int>(w), static_cast<int>(h)};
        return true;
    }

    void Texture::unload() {
        if (m_id) {
            glDeleteTextures(1, &m_id);
            m_id = 0;
            m_size = glm::ivec2{0};
        }
    }

    void Texture::bind(const unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
}
