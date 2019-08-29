/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   TestRectangle.cpp
 * Author: Nathan
 * 
 * Created on 29 mars 2019, 10:42
 */

#include "TestRectangle.h"
#include <iostream>

TestRectangle::TestRectangle(Laphony::Graphics::Engine* gEngine, int maxX, int maxY): Image(rand()%350+50, rand()%350+50, {rand()%230+20, rand()%230+20, rand()%230+20}, gEngine)
{
    Position({rand()%maxX, rand()%maxY});
    _pivot = {rand()%maxX, rand()%maxY};
    //_surface->Alpha(rand()%200 + 55);
}

void TestRectangle::Update()
{
    Angle(Angle() + 0.1);
}



