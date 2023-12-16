// EndScreen.h
#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h" 
#include "cinder/Color.h"
#include "cinder/Text.h" 
#include "cinder/Timer.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class EndScreen {
public:
    void setup();
    void draw();
    void update();
    void mouseDown(cinder::app::MouseEvent event);
    void mouseMove(cinder::app::MouseEvent event);

private:
    cinder::Font titleFont;
    cinder::Font buttonFont;
    cinder::Color C_White;
    cinder::Color C_Pink;
    cinder::Rectf exitButtonRect;
    bool isMouseOverExitButton;

    cinder::Timer blinkTimer;
    bool showText;
};
