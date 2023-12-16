// PerlinSpiral.cpp
#include "PerlinSpiral.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

void PerlinSpiral::setup() {
    rotationSpeed = 0.005f;
    lineLength = 20.0f;
    zoomFactor = 2.5f;
    currentColor = generateColor();
    maxZoom = 8.0f; // Set the maximum zoom level
    minZoom = 2.5f;  // Set the minimum zoom level
    zoomIncrement = 0.01f; // Set the zoom increment
    zoomDirection = 1; // Set the initial zoom direction to zoom in
    saturationBoost = 0.1;
}

void PerlinSpiral::update() {
    // Update rotation, line length, and zoom based on time and Perlin noise
    rotationSpeed = 1.5f; // Set a fixed rotation speed

    lineLength = 20.0f + 2.0f * perlin.fBm(getElapsedSeconds() * 0.1f);

    // Increment the zoom factor based on the zoom direction
    zoomFactor += zoomDirection * zoomIncrement;

    // Change the zoom direction if max or min zoom is reached
    if (zoomFactor >= maxZoom || zoomFactor <= minZoom) {
        zoomDirection *= -1; // Reverse the zoom direction
    }

    // Update the current color using the analogous color function
    float angleSeparation = 30.0f * 0.01f;

    currentColor = calculateAnalogousColor(currentColor, angleSeparation, saturationBoost);
}

void PerlinSpiral::draw() {
    // Set the line width for a more visible effect
    gl::lineWidth(0.1f);

    // Begin drawing lines
    gl::begin(GL_LINES);

    float centerX = getWindowWidth() * 0.5f;
    float centerY = getWindowHeight() * 0.5f;

    for (float theta = 0.0f; theta <= 80.0f * M_PI; theta += 0.01f) {
        // Calculate position of the line
        float radius = lineLength * zoomFactor * theta / 10.0f;
        float x1 = centerX + cos(theta) * radius;
        float y1 = centerY + sin(theta) * radius;

        // Apply Perlin noise to perturb the angle of the line
        float angleNoise = perlin.fBm(x1 * 0.01f, y1 * 0.01f, 0.1f);
        float perturbedTheta = theta + angleNoise * 0.5f;

        float x2 = centerX + cos(perturbedTheta) * radius;
        float y2 = centerY + sin(perturbedTheta) * radius;

        // Rotate the line at a constant rate
        float rotatedX2 = cos(rotationSpeed) * (x2 - x1) - sin(rotationSpeed) * (y2 - y1) + x1;
        float rotatedY2 = sin(rotationSpeed) * (x2 - x1) + cos(rotationSpeed) * (y2 - y1) + y1;

        // Set the color
        gl::color(currentColor);

        // Draw the line
        gl::vertex(vec2(x1, y1));
        gl::vertex(vec2(rotatedX2, rotatedY2));
    }

    // End drawing lines
    gl::end();

    // Reset line width for subsequent drawings
    gl::lineWidth(1.0f);
}