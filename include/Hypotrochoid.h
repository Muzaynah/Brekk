#pragma once
// Hypotrochoid.h
#include "AlgorithmBase.h"
#include "ColorUtility.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

using namespace cinder::app;
using namespace ci;

class Hypotrochoid : public AlgorithmBase, public ColorUtility {
public:
    void setup() override;
    void update() override;
    void draw() override;

private:
    // Include any specific parameters and methods related to hypotrochoids
    float hypotrochoidR, hypotrochoidr, hypotrochoidd, hypotrochoidPhase;
    ci::Color currentColor;
    float hypotrochoidSize;
};