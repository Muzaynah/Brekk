#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Text.h"
#include "cinder/Font.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class S_SetTimer {
public:
    void setup();
    void update();
    void draw();
    void keyDown(KeyEvent event);
    void mouseDown(MouseEvent event);
    void mouseMove(MouseEvent event);
    void setScreenTransitionCallback(const std::function<void()>& callback) {
        screenTransitionCallback = callback;
    }
    float Bx, By;
    int getSelectedMinutes() const { return selectedMinutes; }
    int getSelectedSeconds() const { return selectedSeconds; }


private:
    TextBox minDig;
    TextBox minStr;
    TextBox secDig;
    TextBox secStr;
    TextBox colStr;
    string minInput;
    string secInput;
    int selectedMinutes;
    int selectedSeconds;

    signals::Connection mouseMoveConnection;
    signals::Connection keyDownConnection;
    signals::Connection mouseDownConnection;

    std::function<void()> screenTransitionCallback;
    bool isMinInputFocused;
    int minutes;
    int seconds;
    Font dispFont, textFont;

    Rectf BRect;
    bool isMouseOverB;
};
