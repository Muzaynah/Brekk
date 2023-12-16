#include "TimerScreen.h"
#include "cinder/Rand.h"

Color C_Pink = Color(0.95, 0.2, 0.25);

void S_SetTimer::setup() {
    // Set up initial values
    minutes = 0;
    seconds = 0;
    dispFont = Font(loadFile(getAssetPath("Fonts/StepsMono.otf")), 160);
    textFont = Font(loadFile(getAssetPath("Fonts/StepsMono.otf")), 50);

    // Initialize TextFields for minutes and seconds
    minInput = "00";
    secInput = "00";

    // Set the focus to minutes initially
    isMinInputFocused = true;

    Bx = getWindowWidth() * 0.5 - 150;
    By = getWindowHeight() * 0.5 + 300;
    BRect = Rectf(Bx, By, Bx + 300, By + 60);
    isMouseOverB = false;

    // Create TextBoxes with size, text, font, and color settings
    minDig = TextBox()
        .text("00")
        .font(dispFont)
        .color(Color(1, 1, 1));

    minStr = TextBox()
        .text("MINS")
        .font(textFont)
        .color(C_Pink);

    colStr = TextBox()
        .text(":")
        .font(dispFont)
        .color(Color(1, 1, 1));

    secDig = TextBox()
        .text("00")
        .font(dispFont)
        .color(Color(1, 1, 1));

    secStr = TextBox()
        .text("SECS")
        .font(textFont)
        .color(C_Pink);

    mouseMoveConnection = getWindow()->getSignalMouseMove().connect([this](MouseEvent event) { mouseMove(event); });
    keyDownConnection = getWindow()->getSignalKeyDown().connect([this](KeyEvent event) { keyDown(event); });
    mouseDownConnection = getWindow()->getSignalMouseDown().connect([this](MouseEvent event) { mouseDown(event); });
}

void S_SetTimer::draw() {
    gl::clear(Color(0.1, 0.02, 0.04));

    // Calculate the position for the TextBoxes in the middle of the screen
    vec2 center = vec2(app::getWindowWidth() * 0.5f, app::getWindowHeight() * 0.5f);

    // Set the position for each TextBox
    vec2 minp = center - vec2(200, 200);
    vec2 minstrp = center - vec2(200, -80);
    vec2 colstrp = center - vec2(0, 200);
    vec2 secp = center + vec2(200, -200);
    vec2 secstrp = center + vec2(200, 80);

    // Draw input cursor (blinking effect)
    if (isMinInputFocused && getElapsedFrames() % 60 < 30) {
        gl::drawStringCentered("|", minp + vec2(90, 0), C_Pink, dispFont);  // Move cursor to the right
    }
    else if (!isMinInputFocused && getElapsedFrames() % 60 < 30) {
        gl::drawStringCentered("|", secp + vec2(90, 0), C_Pink, dispFont);  // Move cursor to the right
    }

    // Draw the TextBoxes
    gl::drawStringCentered(minStr.getText(), minstrp, minStr.getColor(), minStr.getFont());
    gl::drawStringCentered(colStr.getText(), colstrp, colStr.getColor(), colStr.getFont());
    gl::drawStringCentered(secStr.getText(), secstrp, secStr.getColor(), secStr.getFont());

    // Draw the first two digits for minutes and seconds
    gl::drawStringCentered(minInput.substr(0, 2), minp, Color(1, 1, 1), dispFont);
    gl::drawStringCentered(secInput.substr(0, 2), secp, Color(1, 1, 1), dispFont);

    {
        Color textColor = isMouseOverB ? C_Pink : Color::white();
        gl::drawStringCentered("SET TIMER", vec2(getWindowWidth() * 0.5, getWindowHeight() * 0.5 + 300), textColor, textFont);
    }
}

void S_SetTimer::update() {
    // Update logic if needed 

    // Update text based on input
    if (isMinInputFocused) {
        minDig.text(minInput);
        // Convert text to integers (you may want to add error handling)
        if (!minInput.empty()) {
            minutes = std::stoi(minInput);
        }
    }
    else {
        secDig.text(secInput);
        // Convert text to integers (you may want to add error handling)
        if (!secInput.empty()) {
            seconds = std::stoi(secInput);
        }
    }
}

void S_SetTimer::mouseMove(MouseEvent event) {
    // Check if the mouse is over the button
    isMouseOverB = BRect.contains(event.getPos());
}

void S_SetTimer::keyDown(ci::app::KeyEvent event) {
    // Handle key press logic

    if (event.getCode() == ci::app::KeyEvent::KEY_RETURN) {
        // Switch focus between minutes and seconds when Enter key is pressed
        isMinInputFocused = !isMinInputFocused;
    }
    else if (event.getCode() == ci::app::KeyEvent::KEY_BACKSPACE) {
        // Handle backspace: Remove the last digit from the input
        if (!isMinInputFocused) {
            if (secInput == "00") {
                // Do nothing if secInput is already "00"
            }
            else if (secInput.size() == 2) {
                secInput.pop_back();
            }
            else if (secInput.size() == 1) {
                secInput = "00";
            }
            // else: Do nothing if secInput is already empty
        }
        else {
            if (minInput == "00") {
                // Do nothing if minInput is already "00"
            }
            else if (minInput.size() == 2) {
                minInput.pop_back();
            }
            else if (minInput.size() == 1) {
                minInput = "00";
            }
            // else: Do nothing if minInput is already empty
        }
    }
    else if (isdigit(event.getChar())) {
        // Append the corresponding digit to the currently focused input
        if (isMinInputFocused) {
            if (minInput == "00") {
                minInput = event.getChar();
            }
            else if (minInput.size() == 1) {
                minInput += event.getChar();
            }
            // else: Do nothing if minInput is already two digits
        }
        else {
            if (secInput == "00") {
                secInput = event.getChar();
            }
            else if (secInput.size() == 1) {
                secInput += event.getChar();
            }
            // else: Do nothing if secInput is already two digits
        }
    }

    // Ensure that both minutes and seconds don't exceed 60
    int enteredMinutes = stoi(minInput);
    int enteredSeconds = stoi(secInput);

    if (enteredMinutes > 59) {
        minInput = "59";
    }

    if (enteredSeconds > 59) {
        secInput = "59";
    }
}

void S_SetTimer::mouseDown(app::MouseEvent event) {
    // Check if the mouse is over button when clicked
    isMouseOverB = BRect.contains(event.getPos());

    if (isMouseOverB && screenTransitionCallback) {
        // Store the selected time
        selectedMinutes = minutes;
        selectedSeconds = seconds;

        // Trigger transition to PatternScreen
        screenTransitionCallback();
    }
}