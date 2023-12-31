// AlgorithmBase.h
#pragma once

class AlgorithmBase {
public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual ~AlgorithmBase() {}
};