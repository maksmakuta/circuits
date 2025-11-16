#include "Font.h"

#include <ft2build.h>
#include <iostream>

#include "glad/gl.h"

#include FT_FREETYPE_H

namespace circuits {

    void Font::load(const std::string& file, const int size) {
    unload();

    m_size = size;

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

    const int first = 32;
    const int last  = 126;
    const int glyphCount = last - first + 1;

    const int cols = 16;
    const int rows = (glyphCount + cols - 1) / cols;

    const int cellW = size * 2;
    const int cellH = size * 2;

    const int atlasW = cols * cellW;
    const int atlasH = rows * cellH;

    std::vector<uint8_t> atlas(atlasW * atlasH, 0);

    // ---- Load glyphs ----
    int index = 0;

    for (uint32_t cp = first; cp <= last; ++cp){
        if (FT_Load_Char(face, cp, FT_LOAD_RENDER)) {
            continue;
        }

        const auto g = face->glyph;

        int cx = (index % cols) * cellW;
        int cy = (index / cols) * cellH;
        index++;

        for (int y = 0; y < g->bitmap.rows; ++y) {
            for (int x = 0; x < g->bitmap.width; ++x) {
                atlas[(cy + y) * atlasW + (cx + x)] =
                    g->bitmap.buffer[y * g->bitmap.pitch + x];
            }
        }

        Glyph glyph{};

        glyph.size   = { g->bitmap.width, g->bitmap.rows };
        glyph.offset = { g->bitmap_left, g->bitmap_top };
        glyph.advance = static_cast<float>(g->advance.x >> 6);

        float u0 = static_cast<float>(cx) / static_cast<float>(atlasW);
        float v0 = static_cast<float>(cy) / static_cast<float>(atlasH);
        float u1 = static_cast<float>(cx + g->bitmap.width)  / static_cast<float>(atlasW);
        float v1 = static_cast<float>(cy + g->bitmap.rows)   / static_cast<float>(atlasH);
        glyph.uv = { u0, v0, u1, v1 };

        m_glyphs[cp] = glyph;
    }

    m_texture.load(atlas, { atlasW, atlasH }, GL_RED);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    }

    void Font::unload() {
        m_texture.unload();
        m_glyphs.clear();
        m_size = 0;
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

    int Font::getSize() const {
        return m_size;
    }

    glm::vec2 Font::textSize(const std::string& text) const {
        float w = 0.0f, h = static_cast<float>(m_size);

        for (const char c : text) {
            if (c == '\n') {
                h += static_cast<float>(m_size);
                w = 0;
                continue;
            }

            auto g = getGlyph(static_cast<uint32_t>(c));
            if (!g) continue;

            w += g->advance;
        }

        return { w, h };
    }

}