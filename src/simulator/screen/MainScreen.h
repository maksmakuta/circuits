#ifndef CIRCUITS_MAINSCREEN_H
#define CIRCUITS_MAINSCREEN_H

#include "MainVM.h"
#include "base/interface/IScreen.h"
#include "ui/widget/Label.h"

namespace circuits {

    class MainScreen final : public IScreen<MainVM>{
    public:
        MainScreen();

        void onInit() override;
        void onDeinit() override;
        void onDraw(Renderer&) override;
        void onUpdate(float dt) override;
        void onEvent(const Event &) override;
    private:
        glm::ivec2 m_view{0};
        std::unique_ptr<Label> m_text = nullptr;
    };

}

#endif //CIRCUITS_MAINSCREEN_H