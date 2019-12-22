/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Music.h
 * Author: nathan
 *
 * Created on December 22, 2019, 9:42 PM
 */

#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL_mixer.h>
#include <string>

namespace Laphony
{
    namespace Sound
    {
        class Music 
        {
            public:
                Music(std::string const& file);
                virtual ~Music();

                static uint8_t GetMusicGlobalVolume();
                static void SetMusicGlobalVolume(uint8_t const& volume);

            private:
                Mix_Music* _music;
                
                static uint8_t volume;
        };
    }
}

#endif /* MUSIC_H */

