/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Music.cpp
 * Author: nathan
 * 
 * Created on December 22, 2019, 9:42 PM
 */

#include "Music.h"
#include "Sound.h"

#include <iostream>

namespace Laphony
{
    namespace Sound
    {
        uint8_t Music::volume = 255;
        
        Music::Music(std::string const& file): _music(Mix_LoadMUS(file.c_str()))
        {
            if(!_music)
            {
                std::cerr << "Music file \"" << file << "\" load error: " << Mix_GetError() << std::endl;
            }
        }
        
        Music::~Music()
        {
            if(_music)
            {
                Mix_FreeMusic(_music);
            }
        }
        
        uint8_t Music::GetMusicGlobalVolume() 
        {
            return volume;
        }
        
        void Music::SetMusicGlobalVolume(const uint8_t& volume) 
        {
            Music::volume = volume;
            
            Mix_VolumeMusic(volume);
        }


    }
}
