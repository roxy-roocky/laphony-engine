/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SoundEngine.h
 * Author: nathan
 *
 * Created on June 20, 2019, 7:47 AM
 */

#ifndef LAPHONY_SOUND_ENGINE_H
#define LAPHONY_SOUND_ENGINE_H

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

namespace Laphony
{
    namespace Sound
    {
        class Engine 
        {
            private:
                static bool wasInit;
                
                std::map<std::string, Mix_Chunk*> _sounds;
                std::map<std::string, Mix_Music*> _musics;
                               
            public:
                Engine(int frequency = 44100, int countOfSoundsChannels = 20);
                ~Engine();
                
        };
    }
}

#endif /* SOUNDENGINE_H */

