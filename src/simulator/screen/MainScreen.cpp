#include "MainScreen.h"

#include "ui/UI.h"

namespace circuits {

    MainScreen::MainScreen(const std::weak_ptr<IContext> &ctx) : UIScreen(ctx) {}

    WidgetPtr MainScreen::onUI() {
        return column({
            label(
                m_viewmodel.counter_str,
                FontRole::Body,
                mod().padding(8).center()
            ),
            row({
                button(
                    "-",
                    [this]{
                        m_viewmodel.decrement();
                    },
                    mod()
                            .size(glm::ivec2{48})
                            .padding(4,8)
                ),
                button(
                    "+",
                    [this]{
                        m_viewmodel.increment();
                    },
                    mod()
                            .size(glm::ivec2{48})
                            .padding(4,8)
                ),
            }, mod().padding(8).center())
        }, mod().center());
    }

}
