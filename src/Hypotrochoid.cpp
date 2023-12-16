// Hypotrochoid.cpp
#include "Hypotrochoid.h"

void Hypotrochoid::setup() {
    // Initialize hypotrochoid-specific parameters
    hypotrochoidR = 110.0f;
    hypotrochoidr = 25.0f;
    hypotrochoidd = 65.0f;
    hypotrochoidPhase = 0.0f;
    hypotrochoidSize = 400.0f; // Initial size

    // Generate the initial color
    currentColor = generateColor();
}

void Hypotrochoid::update() {
    // Update hypotrochoid-specific logic
    float period = 15.0f;

    // Zoom in and out alternately
    hypotrochoidSize = 400.0f + 200.0f * cos(getElapsedSeconds() * 2.0f * M_PI / period);
    hypotrochoidPhase += 0.1f;

    // Update the current color using the analogous color function
    float angleSeparation = 30.0f * 0.01f;
    float saturationBoost = 20;
    currentColor = calculateAnalogousColor(currentColor, angleSeparation, saturationBoost);
}

void Hypotrochoid::draw() {
    gl::lineWidth(0.01f);
    gl::begin(GL_LINE_STRIP);

    for (float t = 0.0f; t <= 150 * M_PI; t += 0.005) {
        float x = getWindowWidth() * 0.5f + (hypotrochoidR - hypotrochoidr) * cos(t) +
            hypotrochoidd * cos((hypotrochoidR - hypotrochoidr) / hypotrochoidr * t + hypotrochoidPhase);
        float y = getWindowHeight() * 0.5f + (hypotrochoidR - hypotrochoidr) * sin(t) -
            hypotrochoidd * sin((hypotrochoidR - hypotrochoidr) / hypotrochoidr * t + hypotrochoidPhase);

        // Scale the entire pattern based on hypotrochoidSize
        x = getWindowWidth() * 0.5f + (x - getWindowWidth() * 0.5f) * hypotrochoidSize / 150.0f;
        y = getWindowHeight() * 0.5f + (y - getWindowHeight() * 0.5f) * hypotrochoidSize / 150.0f;

        // Calculate hue based on time and t
        float hue = fmod(currentColor.r + t * 10.0f, 1.0f) * 360.0f;

        // Use the analogous colors approach
        Color analogousColor = calculateAnalogousColor(currentColor, 30.0f, 30.0f);

        // Set the color
        gl::color(analogousColor);

        // Draw the point
        gl::vertex(vec2(x, y));
    }
    gl::end();
    gl::lineWidth(1.0f);
}