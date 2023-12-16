// Epicycloid.h
#pragma once
#include "AlgorithmBase.h"
#include "ColorUtility.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h" 
using namespace cinder::app;
using namespace ci;

class Epicycloid : public AlgorithmBase, public ColorUtility {
public:
    void setup() override;
    void update() override;
    void draw() override;

private:
    // Include any specific parameters and methods related to epicycloids
    float epicycloidN, epicycloidD, epicycloidSize, epicycloidPhase;
    ci::Color currentColor;
};