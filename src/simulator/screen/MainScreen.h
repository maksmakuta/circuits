#ifndef CIRCUITS_MAINSCREEN_H
#define CIRCUITS_MAINSCREEN_H

#include <memory>

#include "MainVM.h"
#include "core/IScreen.h"
#include "core/IWidget.h"

namespace circuits {

    class MainScreen final : public IScreen {
    public:
        explicit MainScreen(const std::weak_ptr<IContext> &ctx);

        void onInit() override;
        void onDeinit() override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &) override;
    private:
        void onResize(const glm::ivec2& size) const;
        MainVM& viewmodel();

        WidgetPtr m_ui;
        MainVM m_viewmodel;
    };

}

#endif //CIRCUITS_MAINSCREEN_H