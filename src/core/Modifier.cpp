#include "Modifier.h"

#include <memory>
#include <utility>

namespace circuits {

    Padding::Padding() = default;

    Padding::Padding(const int v)
        : Padding{v, v, v, v} {}

    Padding::Padding(const int x, const int y)
        : Padding{x, y, x, y} {}

    Padding::Padding(const int top, const int side, const int bottom)
        : Padding{top, side, bottom, side} {}

    Padding::Padding(const int top, const int left, const int bottom, const int right)
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
        m_gravity |= g;
        return *this;
    }

    Modifier& Modifier::center() {
        return gravity(Gravity::Center);
    }

    Modifier& Modifier::centerV(){
        return gravity(Gravity::VCenter);
    }

    Modifier& Modifier::centerH(){
        return gravity(Gravity::HCenter);
    }

    Modifier& Modifier::top(){
        return gravity(Gravity::Top);
    }

    Modifier& Modifier::bottom(){
        return gravity(Gravity::Bottom);
    }

    Modifier& Modifier::left(){
        return gravity(Gravity::Left);
    }

    Modifier& Modifier::right(){
        return gravity(Gravity::Right);
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

    SizeParams Modifier::getParams() const {
        return m_params;
    }

    Gravity Modifier::getGravity() const {
        return m_gravity;
    }

    Padding Modifier::getPadding() const {
        return m_padding;
    }

    static Theme global_theme{};

    Theme currentTheme() {
        return global_theme;
    }

    ThemeName currentThemeName() {
        return currentTheme().theme;
    }

    void switchTheme() {
        if (currentThemeName() == ThemeName::Dark) {
            setTheme(Theme::getLightTheme());
        }else {
            setTheme(Theme::getDarkTheme());
        }
    }

    void setTheme(Theme t) {
        global_theme = std::move(t);
    }

}
