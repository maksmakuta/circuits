#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit() {

    }

    void MainScreen::onDeinit(){}

    void MainScreen::onDraw(Renderer& r){
        Renderer::clear(Color(0xFF202020));

        r.setGradientType(true);
        r.setGradientAngle(glm::radians(69.f));
        r.setGradientSize(300);
        r.setGradientCenter({350,350});
        r.setGradientColors(Color(0xFFFF0000), Color(0xFF00FFFF));

        r.rect({100,100},{400,400},50);
        r.fillGradient();
    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event &){

    }

}