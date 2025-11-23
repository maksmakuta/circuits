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

    struct Margin {
        Margin();
        explicit Margin(int v);
        Margin(int x, int y);
        Margin(int top, int side, int bottom);
        Margin(int top, int left, int bottom, int right);

        int top{0}, left{0}, bottom{0}, right{0};
    };

    using Padding = Margin;

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
        Modifier& padding(const glm::ivec2& p);
        Modifier& padding(const glm::ivec3& p);
        Modifier& padding(const glm::ivec4& p);

        Modifier& margin(int m);
        Modifier& margin(int vert, int horiz);
        Modifier& margin(int top, int side, int bottom);
        Modifier& margin(int top, int right, int bottom, int left);
        Modifier& margin(const glm::ivec2& m);
        Modifier& margin(const glm::ivec3& m);
        Modifier& margin(const glm::ivec4& m);

        [[nodiscard]] SizeParams getParams() const;
        [[nodiscard]] Gravity getGravity() const;
        [[nodiscard]] Padding getPadding() const;
        [[nodiscard]] Margin getMargin() const;

    private:
        Gravity m_gravity = Gravity::None;
        SizeParams m_params;
        Padding m_padding;
        Margin m_margin;
    };

}

#endif //CIRCUITS_MODIFIER_H