#include "MainScreen.h"

#include "ui/UI.h"

namespace circuits {

    MainScreen::MainScreen(const std::weak_ptr<IContext> &ctx) : UIScreen(ctx) {}

    WidgetPtr MainScreen::onUI() {
        return card(
            column({
                label(
                    "Do you like that UI?",
                    FontRole::Title,
                    mod().padding(8)
                ),
                radiogroup(-1,{
                    radiobutton("Yes"                   , mod().padding(4,8)),
                    radiobutton("Mostly yes"            , mod().padding(4,8)),
                    radiobutton("I don't care at all"   , mod().padding(4,8)),
                    radiobutton("Mostly no"             , mod().padding(4,8)),
                    radiobutton("No"                    , mod().padding(4,8)),
                },mod())
            }),
            mod().center()
        );
    }

}
