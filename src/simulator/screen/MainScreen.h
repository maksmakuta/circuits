#ifndef CIRCUITS_MAINSCREEN_H
#define CIRCUITS_MAINSCREEN_H

#include "base/interface/IScreen.h"
#include "ui/layout/Column.h"

#include "MainVM.h"

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
        std::shared_ptr<Column> m_list = nullptr;
    };

}

#endif //CIRCUITS_MAINSCREEN_H