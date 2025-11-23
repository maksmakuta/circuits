#ifndef CIRCUITS_LABEL_H
#define CIRCUITS_LABEL_H

#include "core/IWidget.h"

namespace circuits {

    class Label final : public IWidget{
    public:
        explicit Label(std::string text = "");

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onLayout(const Rect &) override;
        void onDraw(Renderer &) override;

    private:
        std::string m_text;
    };

}



#endif //CIRCUITS_LABEL_H