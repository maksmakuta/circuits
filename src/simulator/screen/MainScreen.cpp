#include "MainScreen.h"

#include "ui/UI.h"

namespace circuits {

    MainScreen::MainScreen(const std::weak_ptr<IContext> &ctx) : UIScreen(ctx) {}

    WidgetPtr MainScreen::onUI() {
        return column({
            radiobutton(mod().padding(16)),
            radiobutton(mod().padding(8).centerH())
        },mod().center() );
    }

}
