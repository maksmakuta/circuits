#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit() {
    //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        texture.load("../img.png");
    }

    void MainScreen::onDeinit() {
        texture.unload();
    }

    void MainScreen::onDraw(Renderer& r){
        clear(0xFF202020);

        r.rect({50,50},texture.getSize());
        r.fill(texture);
        // r.fill(Color(0xFFFF0000));
        // r.stroke(Color(0xFF00FF00),15);

    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event &){

    }

}
