/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sound.cpp
 * Author: nathan
 * 
 * Created on December 22, 2019, 9:24 PM
 */

#include <locale>

#include "Sound.h"

namespace Laphony
{
    namespace Sound
    {
        Sound::Sound(std::string const& file): _sound(Mix_LoadWAV(file.c_str())), _volume(255)
        {}


        Sound::~Sound() 
        {
            if(_sound)
                Mix_FreeChunk(_sound);
        }
        
        uint8_t Sound::GetVolume() const 
        {
            return _volume;
        }
        void Sound::SetVolume(const uint8_t& volume) 
        {
            _volume = volume;
            
            if(_sound)
                Mix_VolumeMusic(_volume);
            
        }


    }
}

