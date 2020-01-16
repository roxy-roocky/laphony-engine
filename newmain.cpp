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
    
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(32);
    
    Mix_SetSoundFonts("Test/res/8bitsf.SF2");
    Mix_Music* music = Mix_LoadMUS("Test/res/midi.mid");
    
    std::cerr << Mix_GetError() << std::endl;
    
    Mix_PlayMusic(music, 1);

    while(!evEngine.AppQuit())
    {
        fEngine.Update(true);
        

    }
    
    Mix_FreeMusic(music);
    
    Mix_CloseAudio();
    
    return 0;
}

