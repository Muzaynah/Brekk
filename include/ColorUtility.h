// ColorUtility.h
#pragma once
#include "cinder/Color.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h" 
#include "cinder/Color.h"

class ColorUtility {
public:
    ci::Color generateColor();
    ci::Color calculateAnalogousColor(const ci::Color& baseColor, float angleSeparation, float saturationBoost);
    ci::Color rgbToHsv(const ci::Color& rgbColor, float saturationBoost);
    ci::Color smoothColor(int iterationCount, float fractionalPart, double animationTime);
private:
};