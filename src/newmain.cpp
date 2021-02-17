/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */
/* 
 * File:   newmain.cpp
 * Author: Nathan Baumann
 *
 * Created on June 20, 2019, 8:19 PM
 */

#include "Graphics/Engine.h"
#include "Frames/Engine.h"
#include "Events/Engine.h"

using namespace Laphony;

/*
 * 
 */
int main(int argc, char** argv)
{
    Graphics::Engine gEngine("Test Android", 800,600, true, true);
    
    Frames::Engine fEngine(60);
    
    Events::Engine evEngine(true);
    
    fEngine.Register(&gEngine);
    fEngine.Register(&evEngine);
    
    while(!evEngine.AppQuit())
    {
        fEngine.Update(true);
    }
    
    return 0;
}

