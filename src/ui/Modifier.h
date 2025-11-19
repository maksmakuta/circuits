#ifndef CIRCUITS_MODIFIER_H
#define CIRCUITS_MODIFIER_H

#include <cstdint>
#include <glm/vec2.hpp>

namespace circuits {

    enum class ModifierFlags : uint8_t {
        FILL_HEIGHT = 1 << 1,
        FILL_WIDTH  = 1 << 2,

        FILL_PARENT = FILL_HEIGHT | FILL_WIDTH,
    };

    struct Modifier {
        Modifier() = default;

        Modifier& fillParent();
        Modifier& fillWidth();
        Modifier& fillHeight();

        Modifier& margin(const glm::vec2& margin);
        Modifier& margin(int margin);

        Modifier& padding(const glm::vec2& padding);
        Modifier& padding(int padding);

        glm::ivec2  m_margin{0};
        glm::ivec2  m_padding{0};
        uint8_t     m_flags{0};
    };

}

#endif //CIRCUITS_MODIFIER_H