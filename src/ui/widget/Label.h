#ifndef CIRCUITS_LABEL_H
#define CIRCUITS_LABEL_H

#include "core/IWidget.h"
#include "enums/FontRole.h"

namespace circuits {

    class Label : public IWidget{
    public:
        explicit Label(std::string text = "", FontRole r = FontRole::Body);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;

        void setText(std::string text);
        void setFontRole(FontRole value);

        [[nodiscard]] std::string getText() const;
        [[nodiscard]] FontRole getFontRole() const;

    private:
        std::string m_text;
        FontRole m_role;
    };

}



#endif //CIRCUITS_LABEL_H