#ifndef CIRCUITS_LABEL_H
#define CIRCUITS_LABEL_H

#include "base/interface/IWidget.h"

namespace circuits {

    class Label final : public IWidget{
    public:
        explicit Label(std::string  = "", const Modifier& = {});

        glm::ivec2 onMeasure(const glm::ivec2 &max_size) override;
        void onDraw(Renderer &) override;

        void setText(const std::string&);
        [[nodiscard]] std::string getText() const;

    private:
        std::string m_text;
    };

}

#endif //CIRCUITS_LABEL_H