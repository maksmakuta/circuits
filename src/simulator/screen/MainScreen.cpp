#include "MainScreen.h"

#include <SDL3/SDL_keycode.h>

namespace circuits {

    void MainScreen::onInit() {
        font.load("/usr/share/fonts/Adwaita/AdwaitaSans-Regular.ttf",64);
    }

    void MainScreen::onDeinit() {
        font.unload();
    }

    void MainScreen::onDraw(Renderer& r) {
        clear(0xFF202020);
        r.setAlign(Align::Center);
        r.setBaseline(Baseline::Middle);

        const auto clicks = viewmodel.clicks.get();
        r.text(font,std::to_string(clicks),view / 2.f);
    }

    void MainScreen::onUpdate(float dt){ }

    void MainScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = {e.window.width, e.window.height};
        }
        if (e.type == EventType::KeyDown) {
            if (e.key.key == SDLK_SPACE) {
                viewmodel.click();
            }
        }
    }

}
