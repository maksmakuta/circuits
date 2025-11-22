#ifndef CIRCUITS_COLUMN_H
#define CIRCUITS_COLUMN_H

#include "base/interface/IWidget.h"
#include "ui/Modifier.h"

namespace circuits {

    class Column final : public IWidget{
    public:
        Column(const std::initializer_list<WidgetPtr>&, const Modifier& = {});

        glm::ivec2 onMeasure(const glm::ivec2 &max_size) override;
        void onLayout(const Rect&) override;
        void onDraw(Renderer &) override;
        void onEvent(const Event &) override;
    private:
        std::vector<WidgetPtr> m_widgets;
    };

}

#endif //CIRCUITS_COLUMN_H