/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadUpdatable.h
 * Author: nathan
 *
 * Created on November 10, 2019, 12:39 PM
 */

#ifndef THREADUPDATABLE_H
#define THREADUPDATABLE_H

#include <SDL2/SDL.h>


#include "Updatable.h"


namespace Laphony
{
    namespace Frames
    {
        class ThreadUpdatable: public Updatable
        {
            public:
                ThreadUpdatable();
                ThreadUpdatable(const ThreadUpdatable& orig);
                virtual ~ThreadUpdatable();
                
                virtual bool Paused() override;
                
                virtual void Pause(bool pause) override;
                
                void Lock();
                void Unlock();
                
            private:
                SDL_mutex* _mutex;
        };

    }
}

#endif /* THREADUPDATABLE_H */

