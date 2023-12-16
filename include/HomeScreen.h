#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h" 
#include "cinder/Color.h"
#include "cinder/Text.h" 
#include <functional> 

using namespace ci;
using namespace ci::app;
using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random> 

class S_Home {
public:
    void setup();
    void update();
    void draw();
    void mouseDown(MouseEvent event);
    void mouseMove(MouseEvent event);
    void setScreenTransitionCallback(const std::function<void()>& callback) {
        screenTransitionCallback = callback;
    }
    fs::path FontPath1 = getAssetPath("Fonts/GTL001.ttf");
    Font TitleFont;
    fs::path FontPath2 = getAssetPath("Fonts/StepsMono.otf");
    Font SecFont, TextFont;
    Color C_Pink;
    //float B1x, B1y;
    float B2x, B2y;

private:
    //Rectf B1Rect;
    Rectf B2Rect;
    //bool isMouseOverB1;
    bool isMouseOverB2;
    Timer blinkTimer;
    bool showText;
    std::function<void()> screenTransitionCallback;
};