#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit() {

    }

    void MainScreen::onDeinit() {

    }

    void MainScreen::onDraw(Renderer& r){
        clear(0xFF202020);

        r.rect({50,50},{125,125});
        r.fill(Color(0xFFFF0000));
        r.stroke(Color(0xFF00FF00),15);

    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event &){

    }

}
