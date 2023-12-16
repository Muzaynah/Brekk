// Fractal.cpp
#include "MandelbrotSet.h"

void MandelbrotSet::setup() {
    aspectRatio = getWindowAspectRatio();
    maxIterations = 100;

    // Set initial parameters
    minVal = -1.0;
    maxVal = 2.0;
    zoom = 1.0;

    fixedCenterReal = -0.75f;
    fixedCenterImag = 0.0f;

    getWindow()->getSignalMouseDown().connect([this](MouseEvent event) { mouseDown(event); });
    getWindow()->getSignalMouseDrag().connect([this](MouseEvent event) { mouseDrag(event); });
    getWindow()->getSignalMouseUp().connect([this](MouseEvent event) { mouseUp(event); });
    getWindow()->getSignalMouseWheel().connect([this](MouseEvent event) { mouseWheel(event); });

    generateFractal();
}

void MandelbrotSet::update() {
    //zoom *= 1.05; // Adjust this factor for the desired zoom speed
    // Regenerate the fractal with the updated center and zoom level
    generateFractal();
}

void MandelbrotSet::draw() {
    gl::clear(Color(0, 0, 0));
    gl::draw(texture, getWindowBounds());
}
void MandelbrotSet::generateFractal() {
    // Image size
    int imgWidth = getWindowWidth();
    int imgHeight = getWindowHeight();

    // Resize the pixelColors vector to match the image size
    surface = Surface8u(imgWidth, imgHeight, false, SurfaceChannelOrder::RGB);

    // Iterate through pixels
    for (int y = 0; y < imgHeight; ++y) {
        for (int x = 0; x < imgWidth; ++x) {
            // Map pixel coordinates to complex plane with updated zoom
            double realPart = fixedCenterReal + (x - imgWidth / 2.0) / (double)imgWidth * (maxVal - minVal) / zoom;
            double imagPart = fixedCenterImag + (y - imgHeight / 2.0) / (double)imgHeight * 3.0 / zoom;

            // Initialize complex number
            double real = realPart;
            double imag = imagPart;

            int iteration = 0;

            // Mandelbrot Set iteration
            while (iteration < maxIterations) {
                double real2 = real * real;
                double imag2 = imag * imag;

                if (real2 + imag2 > 4.0) {
                    break;  // Escape condition
                }

                double twoRealImag = 2.0 * real * imag;
                real = real2 - imag2 + realPart;
                imag = twoRealImag + imagPart;

                ++iteration;
            }

            // Map iteration count to color with enhanced variation
            double normIteration = iteration / (double)maxIterations;
            double fractionalPart = normIteration;

            // Make the inside of the fractal black
            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;

            // Use smooth coloring function to get the color
            ci::Color pixelColor = ColorUtility::smoothColor(iteration, fractionalPart, app::getElapsedSeconds());

            // Set vibrant colors on the outside
            if (normIteration < 1.0) {
                r = static_cast<uint8_t>(pixelColor.r * 255.0f);
                g = static_cast<uint8_t>(pixelColor.g * 255.0f);
                b = static_cast<uint8_t>(pixelColor.b * 255.0f);
            }

            // Set the color in the Surface
            surface.setPixel(ivec2(x, y), Color8u(r, g, b));
        }
    }

    // Create a texture from the surface
    texture = gl::Texture2d::create(surface);
}

void MandelbrotSet::mouseDown(MouseEvent event) {
    lastMousePos = event.getPos();
    isMouseDragging = true;
}

void MandelbrotSet::mouseDrag(MouseEvent event) {
    if (isMouseDragging) {
        vec2 currentMousePos = event.getPos();
        fixedCenterReal += (lastMousePos.x - currentMousePos.x) / getWindowWidth() * (maxVal - minVal) / zoom;
        fixedCenterImag += (lastMousePos.y - currentMousePos.y) / getWindowHeight() * 3.0 / zoom;
        lastMousePos = currentMousePos;
    }
}

void MandelbrotSet::mouseUp(MouseEvent event) {
    isMouseDragging = false;
}
void MandelbrotSet::mouseWheel(MouseEvent event) {
    // Get the cursor position
    vec2 cursorPos = getWindow()->getMousePos();

    // Adjust the zoom level based on the mouse wheel input
    double zoomIncrement = 1.0 + 0.01 * event.getWheelIncrement(); // Inverted the zoom direction
    zoom *= zoomIncrement; // Multiply by zoomIncrement as before

    // Update the fractal center to keep it centered on the cursor
    fixedCenterReal += (cursorPos.x / getWindowWidth() - 0.5) * (maxVal - minVal) / zoom;
    fixedCenterImag += (cursorPos.y / getWindowHeight() - 0.5) * 3.0 / zoom;
}