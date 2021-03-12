/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/**
 * \file   Events/Engine.h
 * \author Nathan
 *
 * \date april 21 2019, 07:38 PM 
 */

#ifndef EVENTS_ENGINE_H
#define EVENTS_ENGINE_H

#include <SDL2/SDL.h>

#include "../Structs.h"
#include "Control.h"
#include "KeyControl.h"
#include "JoyControl.h"
#include "../Frames/Updatable.h"

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

namespace Laphony
{
    namespace Events
    {
        /**
         * \brief This engine manage all events. If you want to know the state of input, you must ask it.
         */
        class Engine: public virtual Frames::Updatable
        {
            //TODO: Make types neutral from SDL
            public: struct JoyInfo
            {
                SDL_JoystickGUID guid;
                SDL_Joystick* joy;
                int id;
                SDL_Haptic* haptic;
            };
            
            public: enum TouchEventType
            {
                NONE = 0,
                DOWN,
                MOTION,
                UP
            };
            
            public: struct FingerInfo
            {
                int64_t screenID;
                int64_t fingerID;
                float x, y, dx, dy;
                TouchEventType type;
                int32_t timestamp;
                float pressure;
            };
                
            public:
                /**
                 * \brief Construct the events engine.
                 * @param autoFreeRegisteredControls Indicate if Control objects must be freed when the engine is destroying
                 */
                Engine(bool autoFreeRegisteredControls);
                
                /**
                 * \brief Destroy the events engine and free the Control objects if autoFreeRegisteredControls is at true
                 */
                virtual ~Engine();
                
                /**
                 * \brief Update the events and update value of each registered controls
                 */
                virtual void Update();
                
                /**
                 * \brief Register a control 
                 * @param[in] name Name for identify control and query the value
                 * @param[in] control Pointer to the control. If autoFree is true, control is release when egine is destroyed
                 */
                void Register(std::string name, Control* control);
                /**
                 * \brief Unregister a control. /!\ if autoFree is enable, control will be released
                 * @param[in] name Name is the name chosen when registered.
                 */
                void Unregister(std::string name);
                
                /**
                 * \brief Check is the user want end the app
                 * @return true if the window cross is pressed at the last engine update
                 */
                bool AppQuit() const;
                
                /**
                 * \brief Retrieve the value of the control corresponding at the name
                 * @param name Name of the control to check
                 * @return The value as integer of the control at the last engine update. The value depends of the kind of control.
                 */
                int GetValueOf(std::string name) const;
                
                /**
                 * \brief Get the current position of the mouse in screen coordinates.
                 * @return A point with mouse coordinates relative to screen
                 * 
                 * This method does not depend from the engine update. The position in query when the method is called.
                 */
                Point GetMousePosition() const;
   
                /**
                 * \brief Get informations about joystick from id
                 * @param id ID of the joystick you want informations
                 * @return Informations about the joystick
                 */
                JoyInfo* GetJoystickInfo(int id);
                
                
                /**
                 * \brief Play rumble on joystick
                 * @param id ID of the joystick you want to rumble
                 * @param strength The strength of the rumble
                 * @param strength The duration of the rumble
                 */
                void PlayRumbleJoystick(int id, float strength, int duration);
                
                FingerInfo PollTouchEvent();
                FingerInfo PollTouchEvent(int64_t fingerId);
                
            private:
                //Common
                std::map<std::string, Control*> _map;
                bool _autoFree, _appQuit;
                
                std::vector<JoyInfo> _joysticks;
                
                std::map<int64_t, std::queue<FingerInfo>> _fingers;
                
                int _currentJoyID;
                
                void InitJoystickHaptic(JoyInfo* joy);
                
                void LookingJoysticks();
                
                JoyInfo JoyFromString(std::string const& str);
        };
    }
}

#endif /* ENGINE_H */

