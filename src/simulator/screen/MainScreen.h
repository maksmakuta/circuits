#ifndef CIRCUITS_MAINSCREEN_H
#define CIRCUITS_MAINSCREEN_H

#include "MainVM.h"
#include "core/IScreen.h"

namespace circuits {

    class MainScreen final : public IScreen {
    public:
        void onInit() override;
        void onDeinit() override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &) override;
    private:
        void onResize(const glm::ivec2& size);

        MainVM viewmodel;
    };

}

#endif //CIRCUITS_MAINSCREEN_H