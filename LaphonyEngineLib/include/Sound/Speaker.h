/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DedicatedChannel.h
 * Author: nathan
 *
 * Created on December 23, 2019, 4:52 PM
 */

#ifndef DEDICATEDCHANNEL_H
#define DEDICATEDCHANNEL_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <cmath>

#include "../Structs.h"
#include "../Transformable.h"

namespace Laphony
{
    namespace Sound
    {
        class Engine;
        class Speaker: public virtual Transformable
        {
            public:
                Speaker(Engine* engine);
                virtual ~Speaker();
                
                bool IsStickOnListener() const;
                void StickOnListener(bool stick);
                
                void Play(std::string const& name);
                void Pause();
                void Halt();
                
                void IsPaused();
                bool IsPlaying();
                
                uint32_t GetMaxAudibleDistance() const;
                void SetMaxAudibleDistance(uint32_t maxDistance);
                
                virtual void Position(const Point& point) override;
                virtual Point Position() const override;

                
            private:
                int _volume;
                int _channel;
                bool _onListener;
                
                uint32_t _maxDistance;
                
                Engine* _engine;
        };
    }
}

#endif /* DEDICATEDCHANNEL_H */

