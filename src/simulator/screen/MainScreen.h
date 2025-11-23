#ifndef CIRCUITS_MAINSCREEN_H
#define CIRCUITS_MAINSCREEN_H

#include "core/IScreen.h"
#include "MainVM.h"

namespace circuits {

    class MainScreen final : public IScreen {
    public:
        void onInit() override;
        void onDeinit() override;
        void onDraw(Renderer &) override;
        void onUpdate(float) override;
        void onEvent(const Event &) override;
    };

}

#endif //CIRCUITS_MAINSCREEN_H