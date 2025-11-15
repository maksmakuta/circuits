#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit() {

    }

    void MainScreen::onDeinit(){}

    void MainScreen::onDraw(Renderer& r){
        Renderer::clear(Color(0xFF202020));

        r.rect({100,100},{400,400},50);
        r.fill(Color(0xFF606060));
    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event &){

    }

}