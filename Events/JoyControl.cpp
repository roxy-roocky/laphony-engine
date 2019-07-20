/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */
/* 
 * File:   JoyControl.cpp
 * Author: nathan
 * 
 * Created on June 22, 2019, 10:17 AM
 */

#include "JoyControl.h"

#include <sstream>

namespace Laphony
{
    namespace Events
    {
        JoyButtonControl::JoyButtonControl(int joyId, int buttonId): _joyId(joyId), _buttonId(buttonId), _isPressed(false), _lastState(false)
        {}
        
        int JoyButtonControl::Value() const
        {
            return static_cast<int>(_isPressed);
        }
        
        void JoyButtonControl::Value(int value)
        {
            _lastState = _isPressed;
            _isPressed = static_cast<bool>(value);
        }
        
        int JoyButtonControl::JoyID() const 
        {
            return _joyId;
        }
        
        int JoyButtonControl::ButtonID() const 
        {
            return _buttonId;
        }
        
        std::string JoyButtonControl::ToString() const
        {
            std::ostringstream oss;
            oss << "joy " << _joyId << " button " << _buttonId;
            
            return oss.str();
        }

        int JoyButtonControl::LastState() const 
        {
            return static_cast<int>(_lastState);
        }

    }
}

