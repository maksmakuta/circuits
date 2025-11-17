#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit() {
    //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        font.load("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf",16);
    }

    void MainScreen::onDeinit() {
        font.unload();
    }

    void MainScreen::onDraw(Renderer& r) {
        clear(0xFF202020);

        r.rect({10,10},{360,240});
        r.fill(Color(0xFF00FF00));
        r.stroke(Color(0xFFFF00FF),15);

        r.rect({300,300},{256,256});
        r.fill(font.getTexture());

        r.text(font,"Hello, World!", {30,300 + font.getSize()});
    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event &){

    }

}
