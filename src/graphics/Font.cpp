#include "Font.h"

#include <cmath>
#include <iostream>

#include "glad/gl.h"
#include "OpenSans_Regular_ttf.hpp"

namespace circuits {

    constexpr auto atlas_size = glm::ivec2(1024);

    void Font::load(const std::string& file, const int size) {
        unload();
        m_font_data[0] = size;

        FT_Library ft;
        if (FT_Init_FreeType(&ft) != 0) {
            std::cerr << "FreeType: Failed to initialize\n";
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, file.c_str(), 0, &face) != 0) {
            std::cerr << "FreeType: Failed to load font: " << file << "\n";
            FT_Done_FreeType(ft);
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, size);

        build(face);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    void Font::loadDefault(const int size) {
        unload();
        m_font_data[0] = size;

        FT_Library ft;
        if (FT_Init_FreeType(&ft) != 0) {
            std::cerr << "FreeType: Failed to initialize\n";
            return;
        }

        FT_Face face;
        if (FT_New_Memory_Face(ft, OpenSans_Regular_ttf, OpenSans_Regular_ttf_len, 0, &face) != 0) {
            std::cerr << "FreeType: Failed to load default font" << std::endl;
            FT_Done_FreeType(ft);
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, size);

        build(face);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    void Font::unload() {
        m_texture.unload();
        m_glyphs.clear();
        m_font_data = glm::ivec4{0};
    }

    Texture Font::getTexture() const {
        return m_texture;
    }

    std::optional<Glyph> Font::getGlyph(const uint32_t code) const {
        if (m_glyphs.contains(code)) {
            return m_glyphs.at(code);
        }
        return std::nullopt;
    }

    void Font::build(const FT_Face& face) {
        m_font_data[1] = static_cast<int>(face->size->metrics.ascender  >> 6);
        m_font_data[2] = static_cast<int>(face->size->metrics.descender >> 6);
        m_font_data[3] = static_cast<int>(face->size->metrics.height    >> 6);

        std::vector<uint8_t> atlas(atlas_size.x * atlas_size.y, 0);

        glm::ivec2 pos{0};
        int h = 0;
        for (uint32_t cp = 0; cp < 128; ++cp){
            if (FT_Load_Char(face, cp, FT_LOAD_RENDER)) {
                continue;
            }
            if (FT_Get_Char_Index(face, cp) == 0) {
                continue;
            }

            const auto g = face->glyph;

            h = std::max(h,static_cast<int>(g->bitmap.rows));

            if (pos.x + g->bitmap.width + 1 > atlas_size.x) {
                pos.x = 1;
                pos.y += h;
                h = 0;
            }

            for (int y = 0; y < g->bitmap.rows; ++y) {
                for (int x = 0; x < g->bitmap.width; ++x) {
                    atlas[(pos.y + y) * atlas_size.x + (pos.x + x)] =
                        g->bitmap.buffer[y * g->bitmap.pitch + x];
                }
            }

            Glyph glyph{};

            glyph.size   = { g->bitmap.width, g->bitmap.rows };
            glyph.offset = { g->bitmap_left, g->bitmap_top };
            glyph.advance = static_cast<float>(g->advance.x >> 6);

            float u0 = static_cast<float>(pos.x) / static_cast<float>(atlas_size.x);
            float v0 = static_cast<float>(pos.y) / static_cast<float>(atlas_size.y);
            float u1 = static_cast<float>(pos.x + g->bitmap.width)  / static_cast<float>(atlas_size.x);
            float v1 = static_cast<float>(pos.y + g->bitmap.rows)   / static_cast<float>(atlas_size.y);
            glyph.uv = { u0, v0, u1, v1 };

            m_glyphs[cp] = glyph;

            pos.x += static_cast<int>(g->bitmap.width) + 1;
        }

        m_texture.load(atlas, atlas_size, GL_RED);

    }

    int Font::getSize() const {
        return m_font_data[0];
    }

    int Font::getAscent() const{
        return m_font_data[1];
    }

    int Font::getDescent() const{
        return m_font_data[2];
    }

    int Font::getLineHeight() const{
        return m_font_data[3];
    }

    glm::ivec2 Font::textSize(const std::string& text) const {
        int width = 0;

        for (char c : text) {
            auto it = m_glyphs.find(c);
            if (it == m_glyphs.end()) continue;
            width += static_cast<int>(it->second.advance);
        }

        return {width, getAscent() - getDescent()};
    }

}
