/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   Time/Engine.h
 * \author Nathan Baumann
 *
 * \date april 4 2019, 07:22 am
 */

#ifndef LAPHONY_FRAMES_ENGINE_H
#define LAPHONY_FRAMES_ENGINE_H

#include <cstdint>
#include <list>

#include <SDL2/SDL2_framerate.h>

namespace Laphony
{
    /**
     * \brief Contains all entities relative to the time and the frames management
     */
    namespace Frames
    {
        class Updatable;
        
        /**
         * \brief This engine lets you manage the time in your app. It automatically calls the Update method of registered objects at each frame.
         */
        class Engine 
        {
            private: 
                //Denied copy and assign
                Engine(const Engine& o) = default;
                Engine& operator=(const Engine& o) = default;
                
            public: static uint32_t Millis();

            public:
                /**
                 * \brief Create a frame engine with specific framerate
                 * @param fps The count of frames per second
                 */
                Engine(int fps);
                
                /**
                 * \brief Raise objects update if not already raised this frame.
                 * @param wait if true, the method will wait until frame end.
                 * TODO: wait = false
                 */
                void Update(bool wait = true); 
                
                /**
                 * \brief Register an object to be updated each engine frame
                 * @param updatable A pointer to the object
                 * @param placeFront If true, the object will be place at the head of the update list
                 */
                void Register(Updatable* updatable, bool placeFront = false);
                /**
                 * \brief Remove an object from the update list. The object will not be freed.
                 * @param updatable A pointer to the object to remove.
                 */
                void Unregister(Updatable* updatable);
                
                /**
                 * Retrive the frames count of the last second
                 * @return 
                 */
                int LastFPS() const;

            private:
                void WaitFrame(int32_t delay);
                
                std::list<Updatable*> _updatables;

                int _fps;
                FPSmanager _manager;          
                
                uint32_t _beginCountFps;
                int _fpsCount, _lastFps;
 
        };
    }
}

#endif /* ENGINE_H */

