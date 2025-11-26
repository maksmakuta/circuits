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

    SizeParams Modifier::getParams() const {
        return m_params;
    }

    Gravity Modifier::getGravity() const {
        return m_gravity;
    }

    Padding Modifier::getPadding() const {
        return m_padding;
    }

    glm::ivec2 Modifier::applyPadding(const glm::ivec2 &size) const {
        const auto p = getPadding();
        return {
            size.x + p.left + p.right,
            size.y + p.top + p.bottom
        };
    }

    Rect Modifier::applyPadding(const Rect &rect) const {
        const auto p = getPadding();
        return {
            glm::ivec2{
                rect.pos.x + p.left,
                rect.pos.y + p.top
            },
            glm::ivec2{
                rect.size.x + p.left + p.right,
                rect.size.y + p.top + p.bottom
            }
        };
    }

    glm::ivec2 Modifier::applySize(const glm::ivec2 &content, const glm::ivec2 &max) const {
        glm::ivec2 result = content;

        switch (m_params.width.unit) {
            case SizeUnit::Fixed:
                result.x = m_params.width.value;
                break;
            case SizeUnit::Percent:
                result.x = (max.x * m_params.width.value) / 100;
                break;
            default:
                break;
        }

        switch (m_params.height.unit) {
            case SizeUnit::Fixed:
                result.y = m_params.height.value;
                break;
            case SizeUnit::Percent:
                result.y = (max.y * m_params.height.value) / 100;
                break;
            default:
                break;
        }

        return result;
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
