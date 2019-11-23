/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadUpdatable.cpp
 * Author: nathan
 * 
 * Created on November 10, 2019, 12:39 PM
 */

#include <SDL2/SDL_mutex.h>

#include "ThreadUpdatable.h"

namespace Laphony
{
    namespace Frames
    {
        ThreadUpdatable::ThreadUpdatable(): Updatable(), _mutex(SDL_CreateMutex())
        {
        }

        ThreadUpdatable::ThreadUpdatable(const ThreadUpdatable& orig): Updatable(), _mutex(SDL_CreateMutex())
        {
        }

        ThreadUpdatable::~ThreadUpdatable() 
        {
            if(_mutex)
                SDL_DestroyMutex(_mutex);
        }
        
        void ThreadUpdatable::Lock()
        {
            if(_mutex)
                SDL_mutexP(_mutex);
        }
        
        void ThreadUpdatable::Unlock()
        {
            if(_mutex)
                SDL_mutexV(_mutex);
        }
        
        bool ThreadUpdatable::Paused()
        {
            Lock();
            bool isPaused = Updatable::Paused();
            Unlock();
            
            return isPaused;
        }
        
        
        void ThreadUpdatable::Pause(bool pause)
        {
            Lock();
            Updatable::Pause(pause);
            Unlock();
        }
    }
}

