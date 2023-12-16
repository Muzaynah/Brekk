#pragma once
#include "AlgorithmBase.h"
#include "ColorUtility.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h" 
#include <thread>
#include <vector>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MandelbrotSet : public AlgorithmBase, public ColorUtility{
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
    double minVal;
    double maxVal;
    double aspectRatio;
    double zoom;

    double fixedCenterReal;
    double fixedCenterImag;

    ci::gl::Texture2dRef texture;
    ci::Surface8u surface;

    void generateFractal();
    ivec2 lastMousePos;
    bool isMouseDragging = false;
};