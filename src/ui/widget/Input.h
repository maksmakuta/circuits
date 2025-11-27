#ifndef CIRCUITS_INPUT_H
#define CIRCUITS_INPUT_H

#include "core/IWidget.h"
#include "rx/Observable.h"

namespace circuits {

    class Input final : public IWidget{
    public:
        explicit Input(Observable<std::string>& text);

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;
        void onEvent(const Event &e) override;

        void setText(const std::string& text);
        std::string getText() const;

    private:
        std::string m_text;
    };

}

#endif //CIRCUITS_INPUT_H