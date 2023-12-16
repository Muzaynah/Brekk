// JuliaSet.h
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include <vector>
#include "AlgorithmBase.h"
#include "ColorUtility.h"
#include <vector>
#include "cinder/app/MouseEvent.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class JuliaSet : public AlgorithmBase, public ColorUtility {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void mouseDown(MouseEvent event);
    void mouseDrag(MouseEvent event);
    void mouseUp(MouseEvent event);
    void mouseWheel(MouseEvent event);

private:
    int maxIterations;
    double animationTime;
    int currentFrame;
    int totalFrames;
    vec2 constant;
    double zoom;
    vec2 panOffset;
    ivec2 lastMousePos;
    bool isMouseDragging = false;
};