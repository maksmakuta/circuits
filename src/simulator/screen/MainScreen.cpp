#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit(){

    }

    void MainScreen::onDeinit(){

    }

    void MainScreen::onDraw(Renderer& r){
        Renderer::clear(Color(0xFF808080));
        r.rect({100,100}, {250,250});
        r.fill(Color(0xFF00FF00));
    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event &){

    }

}