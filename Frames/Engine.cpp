/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Frames/Engine.cpp
 * Author: Nathan Baumann
 * 
 * Created on 4 avril 2019, 07:22
 */

#include "Engine.h"

#include "Updatable.h"

#include <SDL2/SDL.h>
#include <iostream>

namespace Laphony
{
    namespace Frames
    {
        uint32_t Engine::Millis() 
        {
            return SDL_GetTicks();
        }

        
        Engine::Engine(int fps): _fps(fps), _lastFps(0), _fpsCount(0)
        {
            if(!SDL_WasInit(0))
            {
                SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC);
                atexit(SDL_Quit);
            }
            
            SDL_initFramerate(&_manager);
            SDL_setFramerate(&_manager, _fps);
        }
        
        void Engine::WaitFrame(int32_t delay)
        {
            
            if(delay > 0)
             SDL_Delay(delay);

        }
        
        void Engine::Register(Updatable* updatable, bool placeFront)
        {
            if(placeFront)
                _updatables.push_front(updatable);
            else
                _updatables.push_back(updatable);
        }
        
        void Engine::Unregister(Updatable* updatable)
        {
            _updatables.remove(updatable);
        }
        
        void Engine::Update(bool wait)
        {
            
            //TODO wait = false
            
            Uint32 currentTicks = Millis();
            if(currentTicks - _beginCountFps >= 1000)
            {
                _lastFps = _fpsCount;
                _fpsCount = 0;
                _beginCountFps = Millis();
            }
            _fpsCount++;
            
            
            //Do update
            for(Updatable* updatable : _updatables)
                if(updatable && !updatable->Paused())
                    updatable->Update();
            
             
             
             if(wait)
             {
                 SDL_framerateDelay(&_manager);
             }

        }
        

        int Engine::LastFPS() const 
        {
            return _lastFps;
        }

        
    }
}



