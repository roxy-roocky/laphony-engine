/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadEngine.h
 * Author: nathan
 *
 * Created on November 10, 2019, 12:23 PM
 */

#ifndef THREADENGINE_H
#define THREADENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <string>
#include <list>


namespace Laphony
{
    namespace Frames
    {
        class ThreadUpdatable;
        
        class ThreadEngine
        {
            private:
                //Denied copy and assign
                ThreadEngine(const ThreadEngine& o) = default;
                ThreadEngine& operator=(const ThreadEngine& o) = default;
                
            public:
                ThreadEngine(int fps, std::string const& name);
                ~ThreadEngine();
                
                /**
                 * \brief Register an object to be updated each engine frame
                 * @param updatable A pointer to the object
                 * @param placeFront If true, the object will be place at the head of the update list
                 */
                void Register(ThreadUpdatable* updatable, bool placeFront = false);
                /**
                 * \brief Remove an object from the update list. The object will not be freed.
                 * @param updatable A pointer to the object to remove.
                 */
                void Unregister(ThreadUpdatable* updatable);
                
                /**
                * Retrive the frames count of the last second
                * @return 
                */
                int LastFPS() const;
                
                
            private:
                std::list<ThreadUpdatable*> _updatables;
                SDL_Thread* _thread;
                
                int _fps;
                uint32_t _ticksBegin;          
                
                uint32_t _beginCountFps;
                int _fpsCount, _lastFps;
                
                
                SDL_mutex* _mutex;
                bool _stopRequested;
                
                
                void Update();
                
                
            public: static int Run(void* thEngine);
        };
    }
}

#endif /* THREADENGINE_H */

