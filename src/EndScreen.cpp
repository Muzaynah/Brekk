// EndScreen.cpp
#include "EndScreen.h"
#include "cinder/app/AppBase.h" 

void EndScreen::setup() {
    titleFont = Font(loadFile(getAssetPath("Fonts/StepsMono.otf")), 100);
    buttonFont = Font(loadFile(getAssetPath("Fonts/StepsMono.otf")), 50);
    C_White = Color(1, 1, 1);  // White color
    C_Pink = Color(0.95, 0.2, 0.25);  // Pink color for the button
    getWindow()->getSignalMouseDown().connect([this](MouseEvent event) { mouseDown(event); });
    getWindow()->getSignalMouseMove().connect([this](MouseEvent event) { mouseMove(event); });

    // Set initial button state
    isMouseOverExitButton = false;

    // Calculate the position and size for the button
    vec2 buttonSize(200, 100);
    vec2 buttonPosition = getWindowCenter() + vec2(0, 300);
    exitButtonRect = Rectf(buttonPosition - buttonSize * 0.5f, buttonPosition + buttonSize * 0.5f);

    // Initialize the timer with a duration of 500 milliseconds
    blinkTimer.start(500);
    showText = true;
}

void EndScreen::draw() {
    gl::clear(Color(0.1, 0.02, 0.04));

    // Check if the blink timer has elapsed
    if (blinkTimer.getSeconds() >= 0.5) { // 0.5 seconds interval
        showText = !showText; // Toggle the state
        blinkTimer.start(); // Restart the timer
    }

    // Draw "Your Brekk is up!" in the center of the screen
    if (showText) {
        gl::drawStringCentered("BREKK OVER!", getWindowCenter() + vec2(0, -100), C_Pink, titleFont);
    }

    // Check if the mouse is over the exit button
    if (isMouseOverExitButton) {
        gl::color(C_Pink);
        gl::drawSolidRect(exitButtonRect);
        gl::drawStringCentered("EXIT", exitButtonRect.getCenter() + vec2(0, -40), Color(0.1, 0.02, 0.04), buttonFont);
    }
    else {
        gl::color(C_Pink);
        gl::drawStrokedRect(exitButtonRect);
        gl::drawStringCentered("EXIT", exitButtonRect.getCenter() + vec2(0, -40), C_Pink, buttonFont);
    }
}

void EndScreen::update() {
    // Update logic if needed
}

void EndScreen::mouseDown(MouseEvent event) {
    // Check if the mouse is over the exit button
    if (exitButtonRect.contains(event.getPos())) {
        // Close the application when the button is clicked
        ci::app::AppBase::get()->quit();
    }
}

void EndScreen::mouseMove(MouseEvent event) {
    // Check if the mouse is over the exit button
    isMouseOverExitButton = exitButtonRect.contains(event.getPos());
}
