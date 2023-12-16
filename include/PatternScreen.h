#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h" 
#include "cinder/Color.h"
#include <chrono>

#include "cinder/app/App.h"
#include "cinder/app/KeyEvent.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random> 

#include "AlgorithmBase.h"
#include "Epicycloid.h"
#include <PerlinSpiral.h>
#include <MandelbrotSet.h>
#include <JuliaSet.h>
#include <Hypotrochoid.h>

using namespace std::chrono;
using namespace ci;
using namespace ci::app;
using namespace std;

class S_Pattern {
public:
    void setup();
    void update();
    void draw();
    void drawTimeBar();
    void keyDown(KeyEvent event);
    void mouseDown(MouseEvent event);
    void mouseMove(MouseEvent event);

    void setScreenTransitionCallback(const std::function<void()>& callback) {
        screenTransitionCallback = callback;
    }

    void setSelectedTime(int minutes, int seconds) {
        selectedMinutes = minutes;
        selectedSeconds = seconds;
        remainingMinutes = selectedMinutes;
        remainingSeconds = selectedSeconds;
    }
    void drawInstructionsButton();
    void drawInstructions();
    void toggleInstructions();

private:
    std::function<void()> screenTransitionCallback;
    steady_clock::time_point lastUpdateTime;
    Font font;
    int remainingMinutes;
    int remainingSeconds;
    int selectedMinutes;
    int selectedSeconds;

    enum class AlgorithmType {
        EPICYCLOID,
        PERLINSPIRAL,
        MANDELBROT,
        HYPOTROCHOID,
        JULIASET
    };
    AlgorithmType currentAlgorithm;
    std::unique_ptr<AlgorithmBase> algorithm;
    void setupAlgorithm();
    bool isMouseOverButton;
    bool showInstructions;
    Rectf instructionsButton;
};