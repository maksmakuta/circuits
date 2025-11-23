#ifndef CIRCUITS_MODIFIER_H
#define CIRCUITS_MODIFIER_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "base/Rect.h"
#include "enums/Align.h"
#include "enums/Baseline.h"
#include "enums/SizeType.h"

namespace circuits {

    struct SideData {
        SizeType type;
        int data;
    };

    struct Dimensions {
        explicit Dimensions(SizeType);
        explicit Dimensions(SideData);
        Dimensions(SideData,SideData);
        Dimensions(SizeType, int x, int y);

        SideData width{SizeType::Auto,0};
        SideData height{SizeType::Auto,0};
    };

    class Modifier final {
    public:
        Modifier();

        Modifier& fillParent();
        Modifier& fillWidth();
        Modifier& fillHeight();

        Modifier& asParent(int percent);
        Modifier& asParentWidth(int percent);
        Modifier& asParentHeight(int percent);

        Modifier& fixed(int w, int h);
        Modifier& fixed(const glm::ivec2&);
        Modifier& fixedWidth(int w);
        Modifier& fixedHeight(int h);

        Modifier& align(Align);
        Modifier& alignCenter();
        Modifier& alignLeft();
        Modifier& alignRight();

        Modifier& baseline(Baseline);
        Modifier& baselineTop();
        Modifier& baselineMiddle();
        Modifier& baselineBottom();

        Modifier& padding(int p);
        Modifier& padding(int left, int top, int right, int bottom);
        Modifier& paddingV(const glm::ivec2& p);
        Modifier& paddingV(const glm::ivec4& p);

        Modifier& margin(int m);
        Modifier& margin(int left, int top, int right, int bottom);
        Modifier& marginV(const glm::ivec2& m);
        Modifier& marginV(const glm::ivec4& m);

    protected:
        Align m_align{Align::Left};
        Baseline m_baseline{Baseline::Top};
        Dimensions m_dimensions{SizeType::Auto};
        glm::i16vec4 m_padding{0};
        glm::i16vec4 m_margin{0};
    };

}

#endif //CIRCUITS_MODIFIER_H