#include "HomeScreen.h"

void S_Home::setup() {
    // Setup code for the home screen
    TitleFont = Font(loadFile(FontPath1), 250);
    SecFont = Font(loadFile(FontPath2), 30);
    TextFont = Font(loadFile(FontPath2), 40);
    C_Pink = Color(0.95, 0.2, 0.25);

    //B1x = getWindowWidth() * 0.5-200;
    //B1y = getWindowHeight() * 0.5 + 60;
    B2x = getWindowWidth() * 0.5-90;
    B2y = getWindowHeight() * 0.5 + 90;

    // Set initial button states
    //B1Rect = Rectf(B1x, B1y, B1x+400, B1y+55);
    B2Rect = Rectf(B2x, B2y, B2x+180, B2y+85);

    //isMouseOverB1 = false;
    isMouseOverB2 = false;

    // Initialize the timer with a duration of 500 milliseconds
    blinkTimer.start(500);
    showText = true;

    getWindow()->getSignalMouseDown().connect([this](MouseEvent event) { mouseDown(event); });
    getWindow()->getSignalMouseMove().connect([this](MouseEvent event) { mouseMove(event); });
}

void S_Home::update() {
    // Update code for the home screen

    // Check if the blink timer has elapsed
    if (blinkTimer.getSeconds() >= 0.4) { // 0.5 seconds interval
        showText = !showText; // Toggle the state
        blinkTimer.start(); // Restart the timer
    }
}

void S_Home::draw() {
    // Drawing code for the home screen
    gl::clear(Color(0.1, 0.02, 0.04)); // Dark burgundy background for the home screen
    gl::drawStringCentered("BREKK", vec2(getWindowWidth() * 0.5, getWindowHeight() * 0.5 - 500), C_Pink, TitleFont);
    gl::drawStringCentered("Take a brekk!", vec2(getWindowWidth() * 0.5 + 315, getWindowHeight() * 0.5 - 70), Color::white(), SecFont);

    // Draw the "Choose an activity..." text if showText is true
    if (showText) {
        gl::drawStringCentered("Press to set timer for your digital hourglass...", vec2(getWindowWidth() * 0.5, getWindowHeight() * 0.5 + 320), C_Pink, SecFont);
    }
    /*
    {
        Color textColor = isMouseOverB1 ? C_Pink : Color::white();
        gl::drawStringCentered("Interactive Game", vec2(getWindowWidth() * 0.5, getWindowHeight() * 0.5 + 60), textColor, TextFont);
    }
    */
    // Draw text for geometric visualization
    if (isMouseOverB2)
    {
        gl::color(C_Pink);
        gl::drawSolidRect(B2Rect);
        gl::drawStringCentered("START", vec2(getWindowWidth() * 0.5, getWindowHeight() * 0.5 + 100), Color(0.1, 0.02, 0.04), TextFont);
    }
    else
    {
        gl::color(C_Pink);
        gl::drawStrokedRect(B2Rect);
        gl::drawStringCentered("START", vec2(getWindowWidth() * 0.5, getWindowHeight() * 0.5 + 100), C_Pink, TextFont);
    }
}

void S_Home::mouseMove(MouseEvent event) {
    // Check if the mouse is over the interactive game button
    //isMouseOverB1 = B1Rect.contains(event.getPos());

    // Check if the mouse is over the geometric visualization button
    isMouseOverB2 = B2Rect.contains(event.getPos());
}

void S_Home::mouseDown(MouseEvent event) {
    // Check if the mouse is over the interactive game button when clicked
    //isMouseOverB1 = B1Rect.contains(event.getPos());

    // Check if the mouse is over the geometric visualization button when clicked
    isMouseOverB2 = B2Rect.contains(event.getPos());

    // If the interactive game button is clicked, trigger the callback
    /*if (isMouseOverB1) {
        console() << "Interactive Game Clicked!" << endl;
        
    }
    */
    // If the geometric visualization button is clicked, perform some action
    if (isMouseOverB2) {
        console() << "Geometric Visualization Clicked!" << endl;
        // Add your button click action here
        if (screenTransitionCallback) {
            screenTransitionCallback();
        }
    }
}