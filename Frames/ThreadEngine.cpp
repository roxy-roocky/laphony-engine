/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadEngine.cpp
 * Author: nathan
 * 
 * Created on November 10, 2019, 12:23 PM
 */

#include "ThreadEngine.h"
#include "Engine.h"

#include "ThreadUpdatable.h"

namespace Laphony
{
    namespace Frames
    {
        
        ThreadEngine::ThreadEngine(int fps, std::string const& name): _fps(fps), _lastFps(0), _fpsCount(0), _mutex(SDL_CreateMutex()), _stopRequested(false), _ticksBegin(0)
        {
           
            _thread = SDL_CreateThread(ThreadEngine::Run,name.c_str(),this);
        }

        ThreadEngine::~ThreadEngine() 
        {
            SDL_mutexP(_mutex);
            _stopRequested = true;
            SDL_mutexV(_mutex);
            
            if(_thread)
                SDL_WaitThread(_thread, nullptr);
            
            SDL_DestroyMutex(_mutex);
        }
        
        void ThreadEngine::Register(ThreadUpdatable* updatable, bool placeFront)
        {
            SDL_mutexP(_mutex);
            if(placeFront)
                _updatables.push_front(updatable);
            else
                _updatables.push_back(updatable);
            SDL_mutexV(_mutex);
        }
        
        void ThreadEngine::Unregister(ThreadUpdatable* updatable)
        {
            SDL_mutexP(_mutex);
            _updatables.remove(updatable);
            SDL_mutexV(_mutex);
        }
        
        
        void ThreadEngine::Update()
        {

            Uint32 currentTicks = Engine::Millis();
            if(currentTicks - _beginCountFps >= 1000)
            {
                _lastFps = _fpsCount;
                _fpsCount = 0;
                _beginCountFps = Engine::Millis();
            }
            _fpsCount++;
            
            SDL_mutexP(_mutex);
            //Do update
            for(ThreadUpdatable* updatable : _updatables)
                if(updatable && !updatable->Paused())
                {
                    updatable->Lock();
                    updatable->Update();
                    updatable->Unlock();
                }
            SDL_mutexV(_mutex);
             
            int wait = (1000.0/_fps) - (Engine::Millis() - _ticksBegin);
            
            if(wait > 0)
                SDL_Delay(wait);
            
            _ticksBegin = Engine::Millis();

        }
        
        int ThreadEngine::LastFPS() const 
        {
            return _lastFps;
        }

        
        int ThreadEngine::Run(void* thEngine)
        {
            if(!thEngine)
                return -1;
            
            ThreadEngine* engine = reinterpret_cast<ThreadEngine*>(thEngine);
            
            SDL_mutexP(engine->_mutex); 
            
            while(!engine->_stopRequested)
            {
               SDL_mutexV(engine->_mutex); 
               engine->Update();
               SDL_mutexP(engine->_mutex); 
            }
        }
    }
}

