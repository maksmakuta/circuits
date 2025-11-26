#ifndef CIRCUITS_APPLICATION_H
#define CIRCUITS_APPLICATION_H

#include <string>

#include "core/IContext.h"
#include "window/Window.h"

namespace circuits {

    class Application final : public IContext, public std::enable_shared_from_this<IContext>{
    public:
        Application();

        int run();

        Theme getTheme() override;
        ThemeName getThemeName() override;
        void switchTheme() override;
        void setCursor(Cursor) override;
        void go(const std::shared_ptr<IScreen> &) override;
        void goBack() override;
        glm::ivec2 screenSize() override;

    private:

        Window m_window;
    };

}

#endif //CIRCUITS_APPLICATION_H