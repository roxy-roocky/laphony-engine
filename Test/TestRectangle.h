/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   TestRectangle.h
 * Author: Nathan
 *
 * Created on 29 mars 2019, 10:42
 */

#ifndef TESTRECTANGLE_H
#define TESTRECTANGLE_H

#include "../Graphics/Image.h"

class TestRectangle: public Laphony::Graphics::Image, public Laphony::Frames::Updatable
{
    public:
        TestRectangle(Laphony::Graphics::Engine* gEngine, int maxX = 1000, int maxY = 1000);
        
        virtual void Update();

    private:

};

#endif /* TESTRECTANGLE_H */

