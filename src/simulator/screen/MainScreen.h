#ifndef CIRCUITS_MAINSCREEN_H
#define CIRCUITS_MAINSCREEN_H

#include <memory>

#include "MainVM.h"
#include "core/UIScreen.h"

namespace circuits {

    class MainScreen final : public UIScreen {
    public:
        explicit MainScreen(const std::weak_ptr<IContext> &ctx);

        WidgetPtr onUI() override;

    private:
        MainVM m_viewmodel;
    };

}

#endif //CIRCUITS_MAINSCREEN_H