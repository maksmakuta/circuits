#include "Modifier.h"

namespace circuits {

    uint8_t toInt(ModifierFlags flag) {
        return static_cast<uint8_t>(flag);
    }

    Modifier& Modifier::fillParent() {
        m_flags |= toInt(ModifierFlags::FILL_PARENT);
        return *this;
    }

    Modifier& Modifier::fillWidth() {
        m_flags |= toInt(ModifierFlags::FILL_WIDTH);
        return *this;
    }

    Modifier& Modifier::fillHeight() {
        m_flags |= toInt(ModifierFlags::FILL_HEIGHT);
        return *this;
    }

    Modifier& Modifier::margin(const glm::vec2& margin) {
        m_margin = margin;
        return *this;
    }

    Modifier& Modifier::margin(const int margin) {
        m_margin = glm::ivec2(margin);
        return *this;
    }

    Modifier& Modifier::padding(const glm::vec2& padding) {
        m_padding = padding;
        return *this;
    }

    Modifier& Modifier::padding(const int padding) {
        m_padding = glm::ivec2(padding);
        return *this;
    }

}