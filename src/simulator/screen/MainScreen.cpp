#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit(){

    }

    void MainScreen::onDeinit(){

    }

    void MainScreen::onDraw(Renderer &){
        clear(0xFF00FF00);
    }

    void MainScreen::onUpdate(const float dt){

    }

    void MainScreen::onEvent(const Event& e){
        if (e.type == EventType::WindowResize) {
            onResize({e.window.width, e.window.height});
        }
    }

    void MainScreen::onResize(const glm::ivec2& size) {

    }

}
