#ifndef CIRCUITS_WIDGETUTILS_H
#define CIRCUITS_WIDGETUTILS_H

#include "core/IWidget.h"

namespace circuits {

    class WidgetUtils final {
    public:
        WidgetUtils();

        static glm::ivec2 sizeWithPadding(const WidgetPtr& widget, const glm::ivec2& max_size);
        static glm::ivec2 preferredSize(const SizeParams& params, const glm::ivec2& content,const glm::ivec2& max_size);

        static glm::ivec2 applyVGravity(const Gravity& g, const glm::ivec2& content, const glm::ivec2& max_size);
        static glm::ivec2 applyHGravity(const Gravity& g, const glm::ivec2& content, const glm::ivec2& max_size);
        static glm::ivec2 applyGravity(const Gravity& g, const glm::ivec2& content, const glm::ivec2& max_size);

        static float toPercent(int16_t val);

        static Rect removePadding(const Rect& rect, const Padding& padding);
    };
}


#endif //CIRCUITS_WIDGETUTILS_H