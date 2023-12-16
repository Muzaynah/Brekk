#include "JuliaSet.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void JuliaSet::setup() {
    maxIterations = 100;
    animationTime = 0.0;
    currentFrame = 0;
    totalFrames = 500;

    zoom = 1;
    panOffset = vec2(0.0, 0.0);
    lastMousePos = ivec2(0, 0);
    isMouseDragging = false;

    getWindow()->getSignalMouseDown().connect([this](MouseEvent event) { mouseDown(event); });
    getWindow()->getSignalMouseDrag().connect([this](MouseEvent event) { mouseDrag(event); });
    getWindow()->getSignalMouseUp().connect([this](MouseEvent event) { mouseUp(event); });
    getWindow()->getSignalMouseWheel().connect([this](MouseEvent event) { mouseWheel(event); });
    
    constant = vec2(-0.8, 0.156);
}

void JuliaSet::update() {
    animationTime += 0.01;
    currentFrame++;

    if (currentFrame >= totalFrames) {
        currentFrame = 0;
    }
}

void JuliaSet::draw() {
    gl::clear(Color(0, 0, 0));
    gl::setMatricesWindow(getWindowSize());
    gl::lineWidth(0.5f);
    gl::begin(GL_POINTS);

    double animationTime = app::getElapsedSeconds();

    for (int x = 0; x < getWindowWidth(); x++) {
        for (int y = 0; y < getWindowHeight(); y++) {
            float zx = zoom * (1.5 * (x - getWindowWidth() / 2) / (0.5 * getWindowWidth()) - panOffset.x);
            float zy = zoom * (1.0 * (y - getWindowHeight() / 2) / (0.5 * getWindowHeight()) - panOffset.y);

            float cX = constant.x;
            float cY = constant.y;

            int iteration = 0;
            while (zx * zx + zy * zy < 4.0 && iteration < maxIterations) {
                float xtemp = zx * zx - zy * zy + cX;
                zy = 2.0 * zx * zy + cY;
                zx = xtemp;
                iteration++;
            }

            float normIteration = iteration / static_cast<float>(maxIterations);
            float fractionalPart = normIteration;

            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;

            ci::Color pixelColor = smoothColor(iteration, fractionalPart, animationTime);

            if (normIteration < 1.0) {
                r = static_cast<uint8_t>(pixelColor.r * 255.0f);
                g = static_cast<uint8_t>(pixelColor.g * 255.0f);
                b = static_cast<uint8_t>(pixelColor.b * 255.0f);
            }

            gl::color(Color(r / 255.0f, g / 255.0f, b / 255.0f));
            gl::vertex(vec2(x, y));
        }
    }
    gl::end();
    gl::lineWidth(1.0f);
}

void JuliaSet::mouseDown(MouseEvent event) {
    lastMousePos = event.getPos();
    isMouseDragging = true;
}

void JuliaSet::mouseDrag(MouseEvent event) {
    if (isMouseDragging) {
        vec2 currentMousePos = event.getPos();
        panOffset.x -= (lastMousePos.x - currentMousePos.x) / getWindowWidth() * 2.0 / zoom;
        panOffset.y -= (lastMousePos.y - currentMousePos.y) / getWindowHeight() * 2.0 / zoom;
        lastMousePos = currentMousePos;
    }
}

void JuliaSet::mouseUp(MouseEvent event) {
    isMouseDragging = false;
}

void JuliaSet::mouseWheel(MouseEvent event) {
    // Get the cursor position
    vec2 cursorPos = getWindow()->getMousePos();

    // Adjust the zoom level based on the mouse wheel input
    double zoomIncrement = 1.0 - 0.01 * event.getWheelIncrement();
    zoom *= zoomIncrement;

    // Update the pan offset to keep the fractal centered on the cursor
    panOffset.x -= (cursorPos.x / getWindowWidth() - 0.5) * (1.0 - zoomIncrement) / zoom;
    panOffset.y -= (cursorPos.y / getWindowHeight() - 0.5) * (1.0 - zoomIncrement) / zoom;
}