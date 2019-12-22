/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sound.h
 * Author: nathan
 *
 * Created on December 22, 2019, 9:24 PM
 */

#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>

namespace Laphony
{
    namespace Sound
    {
        class Sound 
        {
            public:
                Sound(std::string const& file);
                virtual ~Sound();

                uint8_t GetVolume() const;
                void SetVolume(uint8_t const& volume);

            private:
                Mix_Chunk* _sound;
                uint8_t _volume;
        };
    }
}

#endif /* SOUND_H */

