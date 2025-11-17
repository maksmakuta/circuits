#include "MainScreen.h"

#include <SDL3/SDL_keycode.h>

namespace circuits {

    void MainScreen::onInit() {
        font.load("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf",32);
    }

    void MainScreen::onDeinit() {
        font.unload();
    }

    void MainScreen::onDraw(Renderer& r) {
        clear(0xFF202020);

        const auto center = glm::vec2(view) / 2.f;

        r.setAlign(align);
        r.setBaseline(baseline);
        r.text(font,"Hello, World!", center);


        r.line(center - glm::vec2(0,50),center + glm::vec2(0,50));
        r.stroke(Color(0xFF00FF00),1.f);
        r.line(center - glm::vec2(100,0),center + glm::vec2(100,0));
        r.stroke(Color(0xFF00FF00),1.f);
    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event& e){
        if (e.type == EventType::WindowResize) {
            view = {e.window.width, e.window.height};
        }
        if (e.type == EventType::KeyDown) {
            if (e.key.key == SDLK_Q) {
                align = Align::Left;
            }else if (e.key.key == SDLK_W) {
                align = Align::Center;
            }else if (e.key.key == SDLK_E) {
                align = Align::Right;
            }if (e.key.key == SDLK_A) {
                baseline = Baseline::Top;
            }else if (e.key.key == SDLK_S) {
                baseline = Baseline::Middle;
            }else if (e.key.key == SDLK_D) {
                baseline = Baseline::Bottom;
            }
        }
    }

}
