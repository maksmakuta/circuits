#include "Modifier.h"

namespace circuits {

    Margin::Margin() = default;

    Margin::Margin(const int v)
        : Margin{v, v, v, v} {}

    Margin::Margin(const int x, const int y)
        : Margin{x, y, x, y} {}

    Margin::Margin(const int top, const int side, const int bottom)
        : Margin{top, side, bottom, side} {}

    Margin::Margin(const int top, const int left, const int bottom, const int right)
        : top(top), left(left), bottom(bottom), right(right) {}

    Modifier& Modifier::fillParent(){
        m_params.width = SizeValue(SizeUnit::Fill);
        m_params.height = SizeValue(SizeUnit::Fill);
        return *this;
    }

    Modifier& Modifier::fillWidth(){
        m_params.width = SizeValue(SizeUnit::Fill);
        return *this;
    }

    Modifier& Modifier::fillHeight(){
        m_params.height = SizeValue(SizeUnit::Fill);
        return *this;
    }

    Modifier& Modifier::asParent(const float percent){
        m_params.width  = SizeValue(SizeUnit::Percent,static_cast<int16_t>(percent * 100.f));
        m_params.height = SizeValue(SizeUnit::Percent,static_cast<int16_t>(percent * 100.f));
        return *this;
    }

    Modifier& Modifier::asParent(const float percent_h, const float percent_v){
        m_params.width  = SizeValue(SizeUnit::Percent,static_cast<int16_t>(percent_v * 100.f));
        m_params.height = SizeValue(SizeUnit::Percent,static_cast<int16_t>(percent_h * 100.f));
        return *this;
    }

    Modifier& Modifier::asParent(const glm::vec2& percent){
        m_params.width  = SizeValue(SizeUnit::Percent,static_cast<int16_t>(percent.x * 100.f));
        m_params.height = SizeValue(SizeUnit::Percent,static_cast<int16_t>(percent.y * 100.f));
        return *this;
    }

    Modifier& Modifier::asWidth(const float percent){
        m_params.width  = SizeValue(SizeUnit::Percent,static_cast<int16_t>(percent * 100.f));
        return *this;
    }

    Modifier& Modifier::asHeight(const float percent){
        m_params.height  = SizeValue(SizeUnit::Percent,static_cast<int16_t>(percent * 100.f));
        return *this;
    }

    Modifier& Modifier::size(const int w, const int h){
        m_params.width  = SizeValue(SizeUnit::Fixed,static_cast<int16_t>(w));
        m_params.height = SizeValue(SizeUnit::Fixed,static_cast<int16_t>(h));
        return *this;
    }

    Modifier& Modifier::size(const glm::vec2& size){
        m_params.width  = SizeValue(SizeUnit::Fixed,static_cast<int16_t>(size.x));
        m_params.height = SizeValue(SizeUnit::Fixed,static_cast<int16_t>(size.y));
        return *this;
    }

    Modifier& Modifier::width(const int val){
        m_params.width  = SizeValue(SizeUnit::Fixed,static_cast<int16_t>(val));
        return *this;
    }

    Modifier& Modifier::height(const int val){
        m_params.height  = SizeValue(SizeUnit::Fixed,static_cast<int16_t>(val));
        return *this;
    }

    Modifier& Modifier::gravity(const Gravity g) {
        m_gravity = g;
        return *this;
    }

    Modifier& Modifier::center() {
        m_gravity = Gravity::Center;
        return *this;
    }

    Modifier& Modifier::padding(const int p) {
        m_padding = Padding(p);
        return *this;
    }

    Modifier& Modifier::padding(const int vert, const int horiz) {
        m_padding = Padding(vert, horiz);
        return *this;
    }

    Modifier& Modifier::padding(const int top, const int side, const int bottom) {
        m_padding = Padding(top, side, bottom);
        return *this;
    }

    Modifier& Modifier::padding(const int top, const int right, const int bottom, const int left) {
        m_padding = Padding(top, right, bottom, left);
        return *this;
    }

    Modifier& Modifier::padding(const glm::ivec2& p) {
        return padding(p.x, p.y);
    }

    Modifier& Modifier::padding(const glm::ivec3& p) {
        return padding(p.x, p.y, p.z);
    }

    Modifier& Modifier::padding(const glm::ivec4& p) {
        return padding(p.x, p.y, p.z, p.w);
    }

    Modifier& Modifier::margin(const int m) {
        m_margin = Margin(m);
        return *this;
    }

    Modifier& Modifier::margin(const int vert, const int horiz) {
        m_margin = Margin(vert, horiz);
        return *this;
    }

    Modifier& Modifier::margin(const int top, const int side, const int bottom) {
        m_margin = Margin(top, side, bottom);
        return *this;
    }

    Modifier& Modifier::margin(const int top, const int right, const int bottom, const int left) {
        m_margin = Margin(top, right, bottom, left);
        return *this;
    }

    Modifier& Modifier::margin(const glm::ivec2& m) {
        return margin(m.x, m.y);
    }

    Modifier& Modifier::margin(const glm::ivec3& m) {
        return margin(m.x, m.y, m.z);
    }

    Modifier& Modifier::margin(const glm::ivec4& m) {
        return margin(m.x, m.y, m.z, m.w);
    }

    SizeParams Modifier::getParams() const {
        return m_params;
    }

    Gravity Modifier::getGravity() const {
        return m_gravity;
    }

    Padding Modifier::getPadding() const {
        return m_padding;
    }

    Margin Modifier::getMargin() const {
        return m_margin;
    }

}