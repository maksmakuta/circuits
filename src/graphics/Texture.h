#ifndef CIRCUITS_TEXTURE_H
#define CIRCUITS_TEXTURE_H

#include <string>
#include <vector>

#include <glm/vec2.hpp>

namespace circuits {

    class Texture {
    public:
        Texture() = default;

        void load(const std::string& file);
        void load(const std::vector<uint8_t>& data, const glm::ivec2& size,int format);

        void unload();
        void bind(uint32_t slot = 0) const;

        [[nodiscard]] glm::uint getHandle() const;
        [[nodiscard]] glm::ivec2 getSize() const;
        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;
    private:
        glm::uint m_id{0};
        glm::i16vec2 m_size{0};
    };

}

#endif //CIRCUITS_TEXTURE_H