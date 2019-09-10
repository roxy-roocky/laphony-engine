/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Events/Engine.cpp
 * Author: Nathan Baumann
 * 
 * Created on 21 avril 2019, 19:38
 */

#include "Engine.h"

bool operator==(SDL_JoystickGUID const& g1, SDL_JoystickGUID const& g2)
{
    bool same = true;

    for(int i=0; i<16; i++)
        if(g1.data[i] != g2.data[i])
        {
            same = false;
            break;
        }

    return same;
}

namespace Laphony
{
    namespace Events
    {
        Engine::Engine(bool autoFreeRegisteredControls):_autoFree(autoFreeRegisteredControls), _appQuit(false), _currentJoyID(0)
        {
            if(!SDL_WasInit(0))
            {
                SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC);
                atexit(SDL_Quit);
            }
        }
                
        Engine::~Engine()
        {
            if(_autoFree)
                for(std::pair<std::string, Control*> entry : _map)
                    if(entry.second)
                        delete entry.second;
        }

        void Engine::Update()
        {
            SDL_Event event;
            while(SDL_PollEvent(&event));
            
            _appQuit = (event.type == SDL_QUIT);
            
       
            
            for(std::pair<std::string, Control*> entry : _map)
                if(entry.second)
                {
                    switch(entry.second->IsType())
                    {
                        case Control::KEY:
                        {
                            KeyControl* kc = dynamic_cast<KeyControl*>(entry.second);
                            kc->Value();
                        }
                        break;
                        
                        case Control::JOY_BUTTON:
                        {
                            JoyButtonControl* jb = dynamic_cast<JoyButtonControl*>(entry.second);
                            
                            
                        } 
                        break;
                        
                        case Control::JOY_HAT:
                        {
                            JoyHatControl* jb = dynamic_cast<JoyHatControl*>(entry.second);
                            
                            if(jb->JoyID() < _joysticks.size())
                            {
                                JoyInfo joy = _joysticks[jb->JoyID()];
                            
                                if(joy.joy)
                                {
                                    jb->Value(SDL_JoystickGetHat(joy.joy, jb->HatID()));
                                }
                            }
                        }
                        break;
                        
                        case Control::JOY_AXIS:
                        {
                            JoyAxisControl* jb = dynamic_cast<JoyAxisControl*>(entry.second);
                            
                            if(jb->JoyID() < _joysticks.size())
                            {
                                JoyInfo joy = _joysticks[jb->JoyID()];
                            
                                if(joy.joy)
                                {
                                    jb->Value(SDL_JoystickGetAxis(joy.joy, jb->AxisID()));
                                }
                            }
                        }
                        break;
                    }
                }
            LookingJoysticks();
        }

        void Engine::Register(std::string name, Control* control)
        {
            //std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            _map.insert(std::pair<std::string, Control*>(name, control));
        }
        
        void Engine::Unregister(std::string name)
        {
            //std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            if(_autoFree)
            {
                std::map<std::string, Control*>::iterator it = _map.find(name);
                if(it->second)
                    delete it->second;
                
                _map.erase(it);
            }
            else
                _map.erase(name);
        }
        
        bool Engine::AppQuit() const
        {
            return _appQuit;
                    
        }
        
        int Engine::GetValueOf(std::string name) const
        {
            //std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            if(_map.count(name))
                return _map.at(name)->Value();
        }

        Point Engine::GetMousePosition() const 
        {
            Point pt;
            
            SDL_GetMouseState(&pt.x, &pt.y);
            
            return pt;
        }

        void Engine::LookingJoysticks()
        {
            int count = SDL_NumJoysticks();
            for(int i=0; i<count ; i++)
            {
                SDL_JoystickGUID newGUID = SDL_JoystickGetDeviceGUID(i);
                bool isNew = true;
                
                for(JoyInfo& joy : _joysticks)
                    if(joy.guid == newGUID)
                    {
                        isNew = false;
                        
                        if(!SDL_JoystickGetAttached(joy.joy))
                        {
                            SDL_JoystickClose(joy.joy);
                            SDL_HapticClose(joy.haptic);
                            
                            joy.joy = SDL_JoystickOpen(i);
                            std::cout << "Events: Reopen Joystick with id " << joy.id << std::endl;
                            
                            InitJoystickHaptic(&joy);
                        }
                        break;
                    }
                
                if(isNew)
                {
                    JoyInfo newJoy;
                    if(newJoy.joy = SDL_JoystickOpen(i))
                    {
                        newJoy.guid = newGUID;
                        newJoy.id = _currentJoyID;
                        
                        _currentJoyID++;                
                        
                        std::cout << "Events: Detect new Joystick with id " << newJoy.id << std::endl;
                        
                        InitJoystickHaptic(&newJoy);                        
                        
                        _joysticks.push_back(newJoy);
                    }
                    
                }
            }
        }
            
        void Engine::InitJoystickHaptic(JoyInfo* joy)
        {
            if(joy->haptic = SDL_HapticOpenFromJoystick(joy->joy))
            {
                if(SDL_HapticRumbleInit( joy->haptic ) == 0)
                {
                    if (SDL_HapticRumblePlay( joy->haptic, 1, 1000 ) != 0)
                        std::cout << "Events: Joystick " << joy->id << " rumble error: " << SDL_GetError() << std::endl;
                }
                else
                    std::cout << "Events: Joystick " << joy->id << " cannot rumble: " << SDL_GetError() << std::endl;
            }
            else
                std::cout << "Events: Joystick " << joy->id << " doesn't have feedback force (haptic): " << SDL_GetError() << std::endl;
        }
        
        Engine::JoyInfo* Engine::GetJoystickInfo(int id)
        {
            if(id < _joysticks.size())
                return &_joysticks[id];
            
            return nullptr;
        }
        
    }
}

