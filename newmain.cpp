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

#include <SDL2/SDL_mixer.h>

using namespace Laphony;

/*
 * 
 */
int main(int argc, char** argv)
{
    Graphics::Engine gEngine("Test Mixer", 800,600, true, true);
    
    Frames::Engine fEngine(60);
    
    Events::Engine evEngine(true);
    
    fEngine.Register(&gEngine);
    fEngine.Register(&evEngine);
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(32);
    
    Mix_Chunk* snd1 = Mix_LoadWAV("snd.wav");
    
    int channel = Mix_PlayChannel(-1, snd1, -1);
    
    Sint16 angle = 0;

    while(!evEngine.AppQuit())
    {
        fEngine.Update(true);
        
        Mix_SetPosition(channel,angle++,0);
    }
    
    Mix_FreeChunk(snd1);
    
    Mix_CloseAudio();
    
    return 0;
}

