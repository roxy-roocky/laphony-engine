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

#include <SDL2/SDL_image.h>
#include <queue>

#include "Engine.h"
#include "MouseButtonControl.h"

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
                IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF|IMG_INIT_WEBP);
                
                atexit(SDL_Quit);
                atexit(IMG_Quit);
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
            while(SDL_PollEvent(&event))
            {
                _appQuit = (event.type == SDL_QUIT);

                /*General event*/
                switch(event.type)
                {
                    case SDL_FINGERDOWN:
                    case SDL_FINGERUP:
                    case SDL_FINGERMOTION:

                    FingerInfo info;
                    info.type = (event.type == SDL_FINGERDOWN ? TouchEventType::DOWN : (event.type == SDL_FINGERUP ? TouchEventType::UP : TouchEventType::MOTION));
                    info.fingerID = event.tfinger.fingerId;
                    info.screenID = event.tfinger.touchId;
                    info.dx = event.tfinger.dx;
                    info.dy = event.tfinger.dy;
                    info.pressure = event.tfinger.pressure;
                    info.timestamp = event.tfinger.timestamp;
                    info.x = event.tfinger.x;
                    info.y = event.tfinger.y;

                    _fingers[info.fingerID].push(info);   

                    break;
                }
            }
        
            const Uint8* keys = SDL_GetKeyboardState(nullptr);
            Uint32 mouseButtons = SDL_GetMouseState(nullptr, nullptr);
            
            for(std::pair<std::string, Control*> entry : _map)
                if(entry.second)
                {
                    switch(entry.second->IsType())
                    {
                        case Control::KEY:
                        {
                            KeyControl* kc = dynamic_cast<KeyControl*>(entry.second);
                            
                            kc->Value(keys[SDL_GetScancodeFromKey(SDL_GetKeyFromName(kc->KeyName().c_str()))]);
                        }
                        break;
                        
                        case Control::MOUSE_BUTTON:
                        {
                            MouseButtonControl* mbc = dynamic_cast<MouseButtonControl*>(entry.second);

                            mbc->Value(SDL_BUTTON(mbc->GetButton()) & mouseButtons);
                        }
                        break;
                        
                        case Control::JOY_BUTTON:
                        {
                            JoyButtonControl* jb = dynamic_cast<JoyButtonControl*>(entry.second);
                            
                            if(jb->JoyID() < _joysticks.size())
                            {
                                JoyInfo joy = _joysticks[jb->JoyID()];
                            
                                if(joy.joy)
                                {
                                    jb->Value(SDL_JoystickGetButton(joy.joy, jb->ButtonID()));
                                }
                            }
                                    
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
            if(_map.count(name) > 0 && _map.at(name))
                return _map.at(name)->Value();
            else
                return 0;
        }

        Point Engine::GetMousePosition() const 
        {
            int x, y;
            
            SDL_GetMouseState(&x, &y);
            
            return Point{static_cast<double>(x),static_cast<double>(y)};
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
                            SDL_Log("Events: Reopen Joystick with id %ld", joy.id);
                            
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
                        
                        SDL_Log("Events: Detect new Joystick with %ld", newJoy.id);
                        
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
                    PlayRumbleJoystick(joy->id, 1, 1000);
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
        
        void Engine::PlayRumbleJoystick(int id, float strength, int duration)
        {
            if(JoyInfo* joy = GetJoystickInfo(id))
            {
                if (SDL_HapticRumblePlay(joy->haptic, strength, duration ) != 0)
                {
                    std::cout << "Events: Joystick " << joy->id << " rumble error: " << SDL_GetError() << std::endl;
                }
            }
        }
        
        Engine::FingerInfo Engine::PollTouchEvent()
        {
            int32_t timestamp = INT32_MAX;
            
            FingerInfo fi;//Create an invalid FingerInfo; Returns it if no events found
            fi.type = NONE;
            
            int64_t selectedFinger = -1;//Use for pop the returned element.
            
            for(const std::pair<int64_t, std::queue<FingerInfo>> &f: _fingers)
            {
                if(f.second.size() > 0 && f.second.front().timestamp < timestamp)
                {
                    fi = f.second.front();
                    timestamp = fi.timestamp;
                    selectedFinger = f.first;
                }
            }
            
            if(selectedFinger >= 0)
            {
                _fingers[selectedFinger].pop();
            }
            
            return fi;
        }
        
        Engine::FingerInfo Engine::PollTouchEvent(int64_t fingerId)
        {
            std::map<int64_t, std::queue<FingerInfo>>::iterator it = _fingers.find(fingerId);
            FingerInfo fi;//Create an invalid FingerInfo; Returns it if no events found
            fi.type = NONE;
            
            if(it != _fingers.end())
            {
                fi = it->second.front();
                it->second.pop();
            }
            
            return fi;
        }
        
    }
}

