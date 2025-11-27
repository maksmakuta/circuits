#ifndef CIRCUITS_UISCREEN_H
#define CIRCUITS_UISCREEN_H

#include <memory>

#include "IScreen.h"
#include "IWidget.h"

namespace circuits {

    class UIScreen : public IScreen{
    public:
        explicit UIScreen(const std::weak_ptr<IContext> &ctx);

        virtual WidgetPtr onUI() = 0;
        virtual void onResize(const WidgetPtr&, const glm::ivec2&) = 0;

        void onInit() override;
        void onDeinit() override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &) override;

    private:
        WidgetPtr m_ui;
        bool m_recompose = true;
    };

}



#endif //CIRCUITS_UISCREEN_H