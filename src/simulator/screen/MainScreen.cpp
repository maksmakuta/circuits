#include "MainScreen.h"

#include <iomanip>
#include <iostream>

namespace circuits {

    void MainScreen::onInit(){
        std::cout << "MainScreen::onInit" << std::endl;
    }

    void MainScreen::onDeinit(){
        std::cout << "MainScreen::onDeinit" << std::endl;
    }

    void MainScreen::onDraw(Renderer &){
        clear(0xFF00FF00);
    }

    void MainScreen::onUpdate(const float dt){
        std::cout << "Delta time: " << std::fixed << std::setprecision(2) << dt << std::endl;
    }

    void MainScreen::onEvent(const Event& ){
        std::cout << "MainScreen::onEvent()" << std::endl;
    }

}
