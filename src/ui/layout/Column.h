#ifndef CIRCUITS_COLUMN_H
#define CIRCUITS_COLUMN_H

#include "base/interface/IWidget.h"

namespace circuits {

    class Column final : public IWidget{
    public:
        Column(const std::initializer_list<WidgetPtr>&);

        glm::ivec2 onMeasure(const glm::ivec2 &max_size) override;
        void onLayout(const glm::ivec2 &pos, const glm::ivec2 &size) override;
        void onDraw(Renderer &) override;
    private:
        std::vector<WidgetPtr> m_widgets;
    };

}

#endif //CIRCUITS_COLUMN_H