#include "Modifier.h"

namespace circuits {

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
        m_padding = glm::ivec4(p);
        return *this;
    }

    Modifier& Modifier::padding(const int vert, const int horiz) {
        m_padding = glm::ivec4(vert, horiz, vert, horiz);
        return *this;
    }

    Modifier& Modifier::padding(const int top, const int sides, const int bottom) {
        m_padding = glm::ivec4(top, sides, bottom, sides);
        return *this;
    }

    Modifier& Modifier::padding(const int top, const int right, const int bottom, const int left) {
        m_padding = glm::ivec4(top, right, bottom, left);
        return *this;
    }

    Modifier& Modifier::padding(const glm::vec2& p) {
        m_padding = glm::ivec4(p.x, p.y, p.x, p.y);
        return *this;
    }

    Modifier& Modifier::padding(const glm::vec3& p) {
        m_padding = {p.x, p.y, p.z, p.y};
        return *this;
    }

    Modifier& Modifier::padding(const glm::vec4& p) {
        m_padding = p;
        return *this;
    }

    Modifier& Modifier::margin(const int m) {
        m_margin = glm::ivec4(m);
        return *this;
    }

    Modifier& Modifier::margin(const int vert, const int horiz) {
        m_margin = glm::ivec4(vert, horiz, vert, horiz);
        return *this;
    }

    Modifier& Modifier::margin(const int top, const int sides, const int bottom) {
        m_margin = glm::ivec4(top, sides, bottom, sides);
        return *this;
    }

    Modifier& Modifier::margin(const int top, const int right, const int bottom, const int left) {
        m_margin = glm::ivec4(top, right, bottom, left);
        return *this;
    }

    Modifier& Modifier::margin(const glm::vec2& m) {
        m_margin = glm::ivec4(m.x,m.y,m.x,m.y);
        return *this;
    }

    Modifier& Modifier::margin(const glm::vec3& m) {
        m_margin = glm::ivec4(m.x,m.y,m.z,m.y);
        return *this;
    }

    Modifier& Modifier::margin(const glm::vec4& m) {
        m_margin = m;
        return *this;
    }

}