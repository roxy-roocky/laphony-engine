/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Sound/Engine.cpp
 * Author: Nathan Baumann
 * 
 * Created on June 20, 2019, 7:47 AM
 */

#include "Engine.h"

namespace Laphony
{
    namespace Sound
    {
        bool Engine::wasInit = false;
        
        Engine::Engine(int frequency, int countOfSoundsChannels) 
        {
            if(!wasInit)
            {
                Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_FLAC|MIX_INIT_FLUIDSYNTH);
                Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, 2, 1024);
                
                atexit(Mix_CloseAudio);
                atexit(Mix_Quit);
                
                wasInit = true;
            }
        }
    }
}
