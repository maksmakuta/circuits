#ifndef CIRCUITS_MODIFIER_H
#define CIRCUITS_MODIFIER_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "enums/Gravity.h"
#include "enums/SizeUnit.h"

namespace circuits {

    struct SizeValue {
        SizeUnit unit = SizeUnit::Auto;
        int16_t value = 0.0f;
    };

    struct SizeParams {
        SizeValue width, height;
    };

    struct Modifier {
        Modifier() = default;

        Modifier& fillParent();
        Modifier& fillWidth();
        Modifier& fillHeight();

        Modifier& asParent(float percent);
        Modifier& asParent(float percent_h,float percent_v);
        Modifier& asParent(const glm::vec2& percent);
        Modifier& asWidth(float percent);
        Modifier& asHeight(float percent);

        Modifier& size(int w, int h);
        Modifier& size(const glm::vec2& size);
        Modifier& width(int);
        Modifier& height(int);

        Modifier& gravity(Gravity);
        Modifier& center();

        Modifier& padding(int p);
        Modifier& padding(int vert, int horiz);
        Modifier& padding(int top, int sides, int bottom);
        Modifier& padding(int top, int right, int bottom, int left);
        Modifier& padding(const glm::vec2& p);
        Modifier& padding(const glm::vec3& p);
        Modifier& padding(const glm::vec4& p);

        Modifier& margin(int m);
        Modifier& margin(int vert, int horiz);
        Modifier& margin(int top, int sides, int bottom);
        Modifier& margin(int top, int right, int bottom, int left);
        Modifier& margin(const glm::vec2& m);
        Modifier& margin(const glm::vec3& m);
        Modifier& margin(const glm::vec4& m);

    private:
        SizeParams m_params;
        Gravity m_gravity = Gravity::None;
        glm::ivec4 m_padding{0};
        glm::ivec4 m_margin{0};
    };

}

#endif //CIRCUITS_MODIFIER_H