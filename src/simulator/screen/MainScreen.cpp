#include "MainScreen.h"

namespace circuits {

    void MainScreen::onInit() {}

    void MainScreen::onDeinit(){}

    void MainScreen::onDraw(Renderer& r){
        Renderer::clear(Color(0xFF808080));

        r.setStrokeCap(StrokeCap::Butt);
        r.line({50,50}, {250,50});
        r.stroke(Color(0xFF00FF00),15);

        r.setStrokeCap(StrokeCap::Square);
        r.line({50,100}, {250,100});
        r.stroke(Color(0xFF00FF00),15);

        r.setStrokeCap(StrokeCap::Round);
        r.line({50,150}, {250,150});
        r.stroke(Color(0xFF00FF00),15);

        auto p = Path();
        p.moveTo({50,50});
        p.lineTo({150,50});
        p.lineTo({100,75});
        p.translate({300,0});
        r.setStrokeJoint(StrokeJoint::Bevel);
        r.path(p);
        r.stroke(Color(0xFF00FF00),15);

        p.translate({0,50});
        r.setStrokeJoint(StrokeJoint::Miter);
        r.path(p);
        r.stroke(Color(0xFF00FF00),15);

        p.translate({0,50});
        r.setStrokeJoint(StrokeJoint::Round);
        r.path(p);
        r.stroke(Color(0xFF00FF00),15);
    }

    void MainScreen::onUpdate(float dt){

    }

    void MainScreen::onEvent(const Event &){

    }

}