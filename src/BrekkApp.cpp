#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "PatternScreen.h"
#include "HomeScreen.h"
#include "TimerScreen.h"
#include "EndScreen.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BrekkApp : public App {
public:
    void setup() override;
    void mouseDown(MouseEvent event) override;
    void keyDown(KeyEvent event) override;
    void update() override;
    void draw() override;

private:
    shared_ptr<S_Home> homeScreen;
    shared_ptr<S_Pattern> patternScreen;
    shared_ptr<S_SetTimer> timerScreen;
    shared_ptr<EndScreen> endScreen;

    enum class AppState { HOME, PATTERN, TIMER, END };
    AppState currentState;

    // State handling functions
    void goToHomeScreen();
    void goToTimerScreen();
    void goToPatternScreen();
    void goToEndScreen();

};

void BrekkApp::setup() {
    setFullScreen(true);
    homeScreen = make_shared<S_Home>();
    patternScreen = make_shared<S_Pattern>();
    timerScreen = make_shared<S_SetTimer>();
    endScreen = make_shared<EndScreen>();

    currentState = AppState::HOME;

    homeScreen->setScreenTransitionCallback([this]() {
        goToTimerScreen();
        });

    patternScreen->setScreenTransitionCallback([this]() {
        goToEndScreen();
        });

    timerScreen->setScreenTransitionCallback([this]() {
        goToPatternScreen();
        });

    switch (currentState) {
    case AppState::HOME:
        homeScreen->setup();
        break;
    case AppState::PATTERN:
        patternScreen->setup();
        break;
    case AppState::TIMER:
        timerScreen->setup();
        break;
    case AppState::END:
        endScreen->setup();
        break;
    default:
        break;
    }
}

void BrekkApp::keyDown(KeyEvent event) {
    if (event.getCode() == KeyEvent::KEY_ESCAPE) {
        setFullScreen(false);
    }
    if (event.getChar() == 'f' || event.getChar() == 'F') {
        setFullScreen(true);
    }
    /*
    switch (currentState) {
    case AppState::HOME:
        if (event.getChar() == 'p' || event.getChar() == 'P') {
            goToPatternScreen();
        }
        else if (event.getChar() == 't' || event.getChar() == 'T') {
            goToTimerScreen();
        }
        break;

    case AppState::PATTERN:
        if (event.getChar() == 'h' || event.getChar() == 'H') {
            goToHomeScreen();
        }
        else if (event.getChar() == 't' || event.getChar() == 'T') {
            goToTimerScreen();
        }
        break;

    case AppState::TIMER:
        if (event.getChar() == 'h' || event.getChar() == 'H') {
            goToHomeScreen();
        }
        break;

    default:
        break;
    }
    */
}

void BrekkApp::mouseDown(MouseEvent event) {
    // Handle mouse down event if needed
}

void BrekkApp::update() {
    switch (currentState) {
    case AppState::HOME:
        homeScreen->update();
        break;
    case AppState::PATTERN:
        patternScreen->update();
        break;
    case AppState::TIMER:
        timerScreen->update();
        break;
    case AppState::END:
        endScreen->update();
        break;
    default:
        break;
    }
}

void BrekkApp::draw() {
    switch (currentState) {
    case AppState::HOME:
        homeScreen->draw();
        break;
    case AppState::PATTERN:
        patternScreen->draw();
        break;
    case AppState::TIMER:
        timerScreen->draw();
        break;
    case AppState::END:
        endScreen->draw();
        break;
    default:
        break;
    }
}

void BrekkApp::goToHomeScreen() {
    currentState = AppState::HOME;
    homeScreen->setup();
}

void BrekkApp::goToEndScreen() {
    currentState = AppState::END;
    endScreen->setup();
}

void BrekkApp::goToTimerScreen() {
    currentState = AppState::TIMER;
    timerScreen->setup();
}

void BrekkApp::goToPatternScreen() {
    currentState = AppState::PATTERN;
    patternScreen->setSelectedTime(timerScreen->getSelectedMinutes(), timerScreen->getSelectedSeconds());
    patternScreen->setup();
}

CINDER_APP(BrekkApp, RendererGl)