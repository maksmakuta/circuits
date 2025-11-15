#ifndef CIRCUITS_MAINSCREEN_H
#define CIRCUITS_MAINSCREEN_H

#include "base/IScreen.h"

namespace circuits {

    class MainScreen final : public IScreen{
    public:
        void onInit() override;
        void onDeinit() override;
        void onDraw(Renderer &) override;
        void onUpdate(float dt) override;
        void onEvent(const Event &) override;
    private:
        glm::vec2 mouse{0,0};
    };

}

#endif //CIRCUITS_MAINSCREEN_H