#ifndef CIRCUITS_FONT_H
#define CIRCUITS_FONT_H

#include <optional>
#include <glm/vec4.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Texture.h"

namespace circuits {

    enum class Align : uint8_t {
        Left,
        Center,
        Right
    };

    enum class Baseline : uint8_t {
        Top,
        Middle,
        Bottom
    };

    struct Glyph {
        glm::vec2 size;
        glm::vec2 offset;
        float advance;
        glm::vec4 uv;
    };

    class Font {
    public:
        Font() = default;

        void load(const std::string&, int size);
        void loadDefault(int size);
        void unload();

        glm::vec2 textSize(const std::string&) const;

        int getSize() const;
        Texture getTexture() const;
        std::optional<Glyph> getGlyph(uint32_t) const;

    private:
        void build(const FT_Face& face);
        int m_size{0};
        Texture m_texture;
        std::unordered_map<uint32_t, Glyph> m_glyphs;
    };

}



#endif //CIRCUITS_FONT_H