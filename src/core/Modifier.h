#ifndef CIRCUITS_MODIFIER_H
#define CIRCUITS_MODIFIER_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Rect.h"
#include "enums/Gravity.h"
#include "enums/SizeUnit.h"
#include "ui/Theme.h"

namespace circuits {

    struct SizeValue {
        SizeUnit unit = SizeUnit::Auto;
        int16_t value = 0.0f;
    };

    struct SizeParams {
        SizeValue width, height;
    };

    struct Padding {
        Padding();
        explicit Padding(int v);
        Padding(int x, int y);
        Padding(int top, int side, int bottom);
        Padding(int top, int left, int bottom, int right);

        int top{0}, left{0}, bottom{0}, right{0};
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
        Modifier& padding(const glm::ivec2& p);
        Modifier& padding(const glm::ivec3& p);
        Modifier& padding(const glm::ivec4& p);

        [[nodiscard]] glm::ivec2 applyPadding(const glm::ivec2& size) const;
        [[nodiscard]] Rect applyPadding(const Rect& rect) const;

        [[nodiscard]] glm::ivec2 applySize(const glm::ivec2& content, const glm::ivec2& max) const;

        [[nodiscard]] SizeParams getParams() const;
        [[nodiscard]] Gravity getGravity() const;
        [[nodiscard]] Padding getPadding() const;

    private:
        Gravity m_gravity = Gravity::None;
        SizeParams m_params{};
        Padding m_padding{};
    };

    Theme currentTheme();
    ThemeName currentThemeName();
    void switchTheme();
    void setTheme(Theme);

    inline Modifier mod(){ return {}; }

}

#endif //CIRCUITS_MODIFIER_H