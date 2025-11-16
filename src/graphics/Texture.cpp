#include "Texture.h"

#include <iostream>

#include "glad/gl.h"
#include "lodePNG/lodepng.h"

namespace circuits {

    void Texture::load(const std::string& file) {
        unload();

        std::vector<unsigned char> png;
        std::vector<unsigned char> pixels;
        unsigned w, h;

        if (const unsigned err = lodepng::decode(pixels, w, h, file); err != 0) {
            std::cerr << "Texture: failed load: " << file
                      << " error: " << lodepng_error_text(err) << "\n";
            return;
        }

        return load(pixels, {w, h}, GL_RGBA);
    }
    void Texture::load(const std::vector<uint8_t>& data, const glm::ivec2& size, const int format) {
        if (!data.data() || size.x <= 0 || size.y <= 0)
            return;

        m_size = size;

        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            m_size.x, m_size.y,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data.data()
        );

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::unload() {
        if (m_id != 0) {
            glDeleteTextures(1, &m_id);
            m_id = 0;
        }
        m_size = glm::ivec2(0);
    }

    void Texture::bind(const uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    glm::uint Texture::getHandle() const {
        return m_id;
    }

    glm::ivec2 Texture::getSize() const {
        return m_size;
    }

    int Texture::getWidth() const {
        return m_size.x;
    }

    int Texture::getHeight() const {
        return m_size.y;
    }

}
