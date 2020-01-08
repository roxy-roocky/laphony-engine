/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Sound/Engine.cpp
 * Author: Nathan Baumann
 * 
 * Created on June 20, 2019, 7:47 AM
 */

#include "Engine.h"
#include "Music.h"
#include "Sound.h"

namespace Laphony
{
    namespace Sound
    {
        bool Engine::wasInit = false;
        Engine* Engine::singleton = nullptr;
        
        //For callback
        void Engine::ChannelEnd(int channel) 
        {
            if(channel >= 0 && channel < singleton->_countOfChannels)
                singleton->_channels[channel] = nullptr;
        }
        
        
        int Engine::GetFirstAvailableChannel() 
        {
            for(int i=0; i<_countOfChannels; i++)
                if(!_channelsDedicated[i] && _channels[i] == nullptr)
                    return i;
            return 0; //Default take first channel and interrupt current sound
        }

        Engine::~Engine()
        {
            if(wasInit)
            {
                Mix_CloseAudio();
                Mix_Quit();
                
                wasInit = false;
                singleton = nullptr;
            }
        }
        
        Engine::Engine(int frequency, int countOfSoundsChannels): _listener(nullptr), _countOfChannels(countOfSoundsChannels), _channels(countOfSoundsChannels, nullptr), _channelsDedicated(countOfSoundsChannels, false)
        {
            if(!wasInit)
            {
                Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_FLAC|MIX_INIT_FLUIDSYNTH);
                Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, 2, 1024);
                
                Mix_ChannelFinished(ChannelEnd);
                           
                
                wasInit = true;
                singleton = this;
            }
            

        }
        
        void Engine::PlayMusic(std::string const& name, int times) 
        {
            Music* music;
            try
            {
                music = _musics.at(name);
            }
            catch(std::out_of_range& ex){music = nullptr;}
            
            if(music && music->_music)
            {
                Mix_PlayMusic(music->_music, times);
                _currentPlayedMusic = name;
            }
        }
        
        void Engine::PlaySound(std::string const& name, int times) 
        {
            Sound* sound;
            try
            {
                sound = _sounds.at(name);
            }
            catch(std::out_of_range& ex){sound = nullptr;}
            
            int channel = GetFirstAvailableChannel();
            
            _channels[channel] = sound;
            
        }
        
        void Engine::StopMusic() 
        {
            Mix_HaltMusic();
            _currentPlayedMusic = "";
        }
        
        void Engine::Register(const std::string& name, Music* music) 
        {
            _musics.insert(std::pair<std::string, Music*>(name, music));
        }

        void Engine::Register(const std::string& name, Sound* sound) 
        {
            _sounds.insert(std::pair<std::string, Sound*>(name, sound));
        }
        
        void Engine::UnregisterMusic(const std::string& name) 
        {
            _musics.erase(name);
        }
        
        void Engine::UnregisterSound(const std::string& name)
        {
            _sounds.erase(name);
        }

        void Engine::StopSound(const std::string& name) 
        {
            Sound* sound;
            try
            {
                sound = _sounds.at(name);
            }
            catch(std::out_of_range& ex){sound = nullptr;}
            
            if(sound)
            {
                for(int i=0; i<_countOfChannels; i++)
                    if(_channels[i] == sound)
                        Mix_HaltChannel(i);
            }
        }
        
        void Engine::PauseMusic() 
        {
            Mix_HaltMusic();
        }
        
        void Engine::ResumeMusic() 
        {
            Mix_ResumeMusic();
        }
        
        void Engine::RewindMusic()
        {
            Mix_RewindMusic();
        }

        void Engine::PauseAll() 
        {
            PauseMusic();
            
            Mix_Pause(-1);
        }
        
        void Engine::ResumeAll() 
        {
            ResumeMusic();
            
            Mix_Resume(-1);
        }
        
        bool Engine::MusicIsPlaying() const 
        {
            return Mix_PlayingMusic() ;
        }
        
        std::string Engine::MusicPlayed() const
        {
            return _currentPlayedMusic;
        }
        
        void Engine::SetListener(Transformable* listener) 
        {
            _listener = listener;
        }
        
        Transformable* Engine::GetListener() const 
        {
            return _listener;
        }


    }
}
