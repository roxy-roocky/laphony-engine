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
#include <vector>

#include "Speaker.h"

namespace Laphony
{
    namespace Sound
    {
        class Music;
        class Sound;
        
        class Engine 
        {
            friend Speaker;
            
            private:
                static bool wasInit;
                static Engine* singleton;
                
                static void ChannelEnd(int channel);
                
                std::map<std::string, Sound*> _sounds;
                std::map<std::string, Music*> _musics;
                
                std::string _currentPlayedMusic;
                
                int _countOfChannels;
                
                std::vector<Sound*> _channels;
                std::vector<bool> _channelsDedicated;
                
                Transformable* _listener;
                
                int GetFirstAvailableChannel();
                               
            public:
                Engine(int frequency = 44100, int countOfSoundsChannels = 50);
                ~Engine();
                
                void Register(std::string const& name, Music* music);
                void Register(std::string const& name, Sound* sound);
                
                void UnregisterMusic(std::string const& name);
                void UnregisterSound(std::string const& name);
                
                void PlayMusic(std::string const& name, int times = -1);
                void PlaySound(std::string const& name, int times = -1);
                
                void StopMusic();
                void StopSound(std::string const& name);
                
                void PauseMusic();
                void ResumeMusic();
                void RewindMusic();
                
                void PauseAll();
                void ResumeAll();
                
                Transformable* GetListener() const;
                void SetListener(Transformable* listener);
                
                bool MusicIsPlaying() const;
                std::string MusicPlayed() const;
        };
    }
}

#endif /* SOUNDENGINE_H */

