#ifndef CIRCUITS_LABEL_H
#define CIRCUITS_LABEL_H

#include "core/IWidget.h"
#include "enums/FontRole.h"

namespace circuits {

    class Label final : public IWidget{
    public:
        explicit Label(std::string text = "", FontRole r = FontRole::Body);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;

    private:
        std::string m_text;
        FontRole m_role;
    };

}



#endif //CIRCUITS_LABEL_H