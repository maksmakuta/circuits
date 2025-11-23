#include "Modifier.h"

namespace circuits {
    Dimensions::Dimensions(const SizeType t)
        : width{t,0}, height{t,0} {}

    Dimensions::Dimensions(const SideData d)
        : width{d}, height{d} {}

    Dimensions::Dimensions(const SideData x,const SideData y)
        : width{x}, height{y}{}

    Dimensions::Dimensions(const SizeType t, const int x, const int y)
        : width{t,x}, height{t,y} {}

    Modifier::Modifier() = default;

    Modifier& Modifier::fillParent() {
        m_dimensions = Dimensions(SizeType::Fill);
        return *this;
    }

    Modifier& Modifier::fillWidth() {
        m_dimensions.width.type = SizeType::Fill;
        return *this;
    }

    Modifier& Modifier::fillHeight() {
        m_dimensions.height.type = SizeType::Fill;
        return *this;
    }

    Modifier& Modifier::asParent(const int percent) {
        m_dimensions = Dimensions{SizeType::Percent, percent, percent};
        return *this;
    }

    Modifier& Modifier::asParentWidth(const int percent) {
        m_dimensions.width = SideData(SizeType::Percent, percent);
        return *this;
    }

    Modifier& Modifier::asParentHeight(const int percent) {
        m_dimensions.height = SideData(SizeType::Percent, percent);
        return *this;
    }

    Modifier& Modifier::align(const Align a) {
        m_align = a;
        return *this;
    }

    Modifier& Modifier::fixed(const int w, const int h) {
        m_dimensions = Dimensions{SizeType::Fill, w, h};
        return *this;
    }

    Modifier& Modifier::fixed(const glm::ivec2& size) {
        return fixed(size.x, size.y);
    }

    Modifier& Modifier::fixedWidth(const int w) {
        m_dimensions.width = SideData(SizeType::Percent, w);
        return *this;
    }

    Modifier& Modifier::fixedHeight(const int h) {
        m_dimensions.height = SideData(SizeType::Percent, h);
        return *this;
    }

    Modifier& Modifier::alignCenter() {
        return align(Align::Center);
    }

    Modifier& Modifier::alignLeft() {
        return align(Align::Left);
    }

    Modifier& Modifier::alignRight() {
        return align(Align::Right);
    }

    Modifier& Modifier::baseline(const Baseline b) {
        m_baseline = b;
        return *this;
    }

    Modifier& Modifier::baselineTop() {
        return baseline(Baseline::Top);
    }

    Modifier& Modifier::baselineMiddle() {
        return baseline(Baseline::Middle);
    }

    Modifier& Modifier::baselineBottom() {
        return baseline(Baseline::Bottom);
    }

    Modifier& Modifier::padding(const int p) {
        return paddingV(glm::ivec4{p});
    }

    Modifier& Modifier::padding(const int left, const int top, const int right, const int bottom) {
        return paddingV(glm::ivec4{left,top,right,bottom});
    }

    Modifier& Modifier::paddingV(const glm::ivec2& p) {
        return paddingV({p.x, p.y,p.x, p.y});
    }

    Modifier& Modifier::paddingV(const glm::ivec4& p) {
        m_padding = p;
        return *this;
    }

    Modifier& Modifier::margin(const int m){
        return marginV(glm::ivec4{m});
    }

    Modifier& Modifier::margin(const int left, const int top, const int right, const int bottom){
        return marginV({left, top, right, bottom});
    }

    Modifier& Modifier::marginV(const glm::ivec2& m){
        return marginV({m.x,m.y,m.x,m.y});
    }

    Modifier& Modifier::marginV(const glm::ivec4& m) {
        m_margin = m;
        return *this;
    }

}
