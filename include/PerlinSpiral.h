// PerlinSpiral.h
#pragma once

#include "AlgorithmBase.h"
#include "ColorUtility.h"
#include "cinder/Perlin.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class PerlinSpiral : public AlgorithmBase, public ColorUtility {
public:
    void setup() override;
    void update() override;
    void draw() override;

private:
    float rotationSpeed, lineLength, zoomFactor, zoomIncrement, minZoom, maxZoom;
    int zoomDirection;
    Color currentColor;
    Perlin perlin;
    float saturationBoost;
};