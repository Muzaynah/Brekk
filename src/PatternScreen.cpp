#include "PatternScreen.h"

void S_Pattern::setup() {
    remainingMinutes = selectedMinutes;
    remainingSeconds = selectedSeconds;

    font = Font(loadFile(getAssetPath("Fonts/StepsMono.otf")), 24);

    currentAlgorithm = AlgorithmType::EPICYCLOID;  // Set the initial algorithm
    setupAlgorithm();

    getWindow()->getSignalKeyDown().connect([this](app::KeyEvent event) { keyDown(event); });
    getWindow()->getSignalMouseDown().connect([this](app::MouseEvent event) { mouseDown(event); });
    getWindow()->getSignalMouseMove().connect([this](app::MouseEvent event) { mouseMove(event); });
    showInstructions = false;
    instructionsButton = Rectf(15, 15, 60, 60);
}

void S_Pattern::update() {
    // Handle key events for changing algorithms
    //auto& window = app::getWindow();

    // Update the current algorithm
    algorithm->update();

    steady_clock::time_point currentTime = steady_clock::now();
    duration<double> elapsedSeconds = duration_cast<duration<double>>(currentTime - lastUpdateTime);

    // Update the timer only if a second has passed
    if (elapsedSeconds.count() >= 1.0) {
        lastUpdateTime = currentTime;  // Update last update time

        if (remainingMinutes > 0 || remainingSeconds > 0) {
            // Decrement the timer
            if (remainingSeconds == 0) {
                remainingMinutes--;
                remainingSeconds = 59;
            }
            else {
                remainingSeconds--;
            }
        }
        else {
            // Transition to HomeScreen when the timer reaches zero
            screenTransitionCallback();
        }
    }
}

void S_Pattern::draw() {
    gl::clear();

    algorithm->draw();
    drawTimeBar();

    if (showInstructions) {
        drawInstructions();
    }

    drawInstructionsButton();
}

void S_Pattern::drawTimeBar() {
    // Calculate the width of the time bar based on the remaining time
    float totalTime = selectedMinutes * 60.0f + selectedSeconds;
    float remainingTime = remainingMinutes * 60.0f + remainingSeconds;
    float barHeight = (getWindowHeight()-300) * (remainingTime / totalTime);

    // Draw the time bar to the side of the screen
    gl::color(Color(1, 1, 1)); //(0.8f, 0.2f, 0.2f)
    gl::drawStrokedRect(Rectf(100, 150, 110, getWindowHeight() - 150));
    gl::drawSolidRect(Rectf(100, getWindowHeight() - barHeight - 150, 110, getWindowHeight() - 150));
}

void S_Pattern::setupAlgorithm() {
    // Create and setup the new algorithm based on the current algorithm type
    switch (currentAlgorithm) {
    case AlgorithmType::EPICYCLOID:
        algorithm = std::make_unique<Epicycloid>();
        break;
    case AlgorithmType::PERLINSPIRAL:
        algorithm = std::make_unique<PerlinSpiral>();
        break;

    case AlgorithmType::HYPOTROCHOID:
        algorithm = std::make_unique<Hypotrochoid>();
        break;
    case AlgorithmType::JULIASET:
        algorithm = std::make_unique<JuliaSet>();
        break;
    case AlgorithmType::MANDELBROT:
        algorithm = std::make_unique<MandelbrotSet>();
        break;
        // Add more cases for additional algorithms
    }
    algorithm->setup();
}

void S_Pattern::keyDown(app::KeyEvent event) {
    // Check for specific key codes
    switch (event.getCode()) {
    case app::KeyEvent::KEY_1:
        currentAlgorithm = AlgorithmType::EPICYCLOID;
        setupAlgorithm();
        break;
    case app::KeyEvent::KEY_2:
        currentAlgorithm = AlgorithmType::HYPOTROCHOID;
        setupAlgorithm();
        break;
    case app::KeyEvent::KEY_3:
        currentAlgorithm = AlgorithmType::PERLINSPIRAL;
        setupAlgorithm();
        break;
    case app::KeyEvent::KEY_4:
        currentAlgorithm = AlgorithmType::MANDELBROT;
        setupAlgorithm();
        break;
    case app::KeyEvent::KEY_5:
        currentAlgorithm = AlgorithmType::JULIASET;
        setupAlgorithm();
        break;
        // Add more cases for other keys if needed
    }
}

void S_Pattern::drawInstructionsButton() {
    // Draw the instructions button
    gl::color(Color(0.95, 0.2, 0.25));
    //gl::drawStringCentered("?", instructionsButton.getCenter() + vec2(0, -20), Color(1,1,1), font);
    if (isMouseOverButton) {
        gl::color(Color(0.95, 0.2, 0.25));
        gl::drawSolidRect(instructionsButton);
        gl::drawStringCentered("?", instructionsButton.getCenter() + vec2(0, -20), Color(0, 0, 0), font);
    }
    else {
        gl::drawStrokedRect(instructionsButton);
        gl::drawStringCentered("?", instructionsButton.getCenter() + vec2(0, -20), Color(1, 1, 1), font);
    }
}

void S_Pattern::drawInstructions() {
    // Draw the instructions box
    gl::color(ColorA(0.0f, 0.0f, 0.0f, 0.8f)); // Semi-transparent black background
    gl::drawSolidRect(getWindowBounds());

    // Draw text instructions
    gl::color(Color(1, 1, 1)); // White text
    gl::drawString("INSTRUCTIONS:\n\n\nYou can switch between different modes by pressing the keys 1-5:\n\n1- Epicycloid Animation\n2- Hypotrochoid Animation\n3- Spiral Animation\n4- Mandelbrot Set Fractal\n5- Julia Set Fractal\n\n\nIn modes 4 and 5, interact with the fractals:\n\n- Drag to move\n- Scroll to zoom in or out\n\n\nThe time bar on the left shows your remaining time.\n\n\nPress the help button again to close instructions...", vec2(150, 100), Color(1,1,1), font);
}

void S_Pattern::mouseDown(app::MouseEvent event) {
    // Check if the mouse click is inside the instructions button
    if (instructionsButton.contains(event.getPos())) {
        toggleInstructions();
    }
}

void S_Pattern::mouseMove(MouseEvent event) {
    // Check if the mouse is over the exit button
    isMouseOverButton = instructionsButton.contains(event.getPos());
}

void S_Pattern::toggleInstructions() {
    // Toggle the instructions display
    showInstructions = !showInstructions;
}