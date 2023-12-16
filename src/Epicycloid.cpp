// Epicycloid.cpp
#include "Epicycloid.h"

void Epicycloid::setup() {
    // Initialize epicycloid-specific parameters
    epicycloidN = 7.0f;
    epicycloidD = 21.0f;
    epicycloidSize = 250.0f;
    epicycloidPhase = 0.0f;

    // Generate the initial color
    currentColor = generateColor();
}

void Epicycloid::update() {
    // Update epicycloid-specific logic
    float period = 9.0f;
    float period2 = 40.0f;
    epicycloidSize = 250.0f + 250.0f * 0.5f * (1.0f + cos(getElapsedSeconds() * 2.0f * M_PI / period));
    epicycloidPhase += 0.005f;

    float nOscillation = 5.0f + 2.0f * 0.5f * (1.0f + cos(getElapsedSeconds() * 0.2 * 2.0f * M_PI / period2));
    epicycloidN = nOscillation;

    // Update the current color using the analogous color function
    float angleSeparation = 30.0f * 0.01f;
    float saturationBoost = 20;
    currentColor = calculateAnalogousColor(currentColor, angleSeparation, saturationBoost);
}

void Epicycloid::draw() {

    gl::lineWidth(0.01f);
    gl::begin(GL_LINE_STRIP);

    for (float t = 0.0f; t <= 150 * M_PI; t += 0.005) {
        float x = getWindowWidth() * 0.5f + cos(t) * cos(epicycloidN / epicycloidD * t + epicycloidPhase) * epicycloidSize;
        float y = getWindowHeight() * 0.5f + cos(t) * sin(epicycloidN / epicycloidD * t + epicycloidPhase) * epicycloidSize;

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