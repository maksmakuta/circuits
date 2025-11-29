#include "WidgetUtils.h"

namespace circuits {

    WidgetUtils::WidgetUtils() = default;

    glm::ivec2 WidgetUtils::sizeWithPadding(const WidgetPtr& widget, const glm::ivec2& max_size) {
        const auto mod = widget->getModifier();
        const auto pad = mod.getPadding();
        const auto content = widget->onMeasure(max_size);
        return content + glm::ivec2(pad.right + pad.left, pad.top + pad.bottom);
    }

    glm::ivec2 WidgetUtils::preferredSize(
        const SizeParams &params,
        const glm::ivec2 &content,
        const glm::ivec2 &max_size
    ) {
        auto size = content;

        switch(params.width.unit) {
            case SizeUnit::Fill:
                size.x = max_size.x;
                break;
            case SizeUnit::Fixed:
                size.x = params.width.value;
                break;
            case SizeUnit::Percent:
                size.x = static_cast<int>(static_cast<float>(max_size.x) * toPercent(params.width.value));
                break;
            default:
                break;
        }

        switch(params.height.unit) {
            case SizeUnit::Fill:
                size.y = max_size.y;
                break;
            case SizeUnit::Fixed:
                size.y = params.height.value;
                break;
            case SizeUnit::Percent:
                size.y = static_cast<int>(static_cast<float>(max_size.y) * toPercent(params.height.value));
                break;
            default:
                break;
        }

        return size;
    }

    float WidgetUtils::toPercent(const int16_t val) {
        return static_cast<float>(val) / 100.f;
    }

    glm::ivec2 WidgetUtils::applyVGravity(const Gravity& g, const glm::ivec2& content,const glm::ivec2& max_size) {
        if (any(g, Gravity::HCenter))
            return {max_size.x / 2 - content.x / 2,0};
        if (any(g, Gravity::Right))
            return {max_size.x - content.x ,0};
        return {0,0};

    }

    glm::ivec2 WidgetUtils::applyHGravity(const Gravity& g, const glm::ivec2& content,const glm::ivec2& max_size) {

    }

    glm::ivec2 WidgetUtils::applyGravity(const Gravity& g, const glm::ivec2& content,const glm::ivec2& max_size) {

    }


}
