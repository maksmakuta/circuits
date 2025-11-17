#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit() {
    //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        font.load("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf",32);

    }

    void MainScreen::onDeinit() {
        font.unload();
    }

    void MainScreen::onDraw(Renderer& r) {
        clear(0xFF202020);
        r.text(font,"Hello, World!", {0,font.getSize()});

        r.rect({0,32},{512,512});
        r.fill(font.getTexture());
    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event &){

    }

}
