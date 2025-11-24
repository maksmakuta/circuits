#ifndef CIRCUITS_INPUT_H
#define CIRCUITS_INPUT_H

#include "core/IWidget.h"

namespace circuits {

    class Input final : public IWidget{
    public:
        explicit Input(std::string);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;
        void onEvent(const Event &e) override;
    private:
        std::string m_text;
    };

}

#endif //CIRCUITS_INPUT_H