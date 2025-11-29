#include "MainScreen.h"

#include "ui/UI.h"

namespace circuits {

    MainScreen::MainScreen(const std::weak_ptr<IContext> &ctx) : UIScreen(ctx) {}

    WidgetPtr MainScreen::onUI() {
        return card(
            column({
                label("Hello", FontRole::Label,mod().padding(4)),
                toggle(false,mod().padding(4)),
                checkbox(false,mod().padding(4)),
                radiobutton(mod().padding(4)),
            }),
            mod().center()
        );
    }

}
