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

        int JoyButtonControl::LastValue() const 
        {
            return static_cast<int>(_lastState);
        }
        
        
        
        
        //Hat

        JoyHatControl::JoyHatControl(int joyID, int hatID): _joyId(joyID), _hatId(hatID), _value(CENTER), _lastValue(CENTER)
        {}
        
        
        int JoyHatControl::Value() const
        {
            return _value;
        }
        
        void JoyHatControl::Value(int value)
        {
            _lastValue = _value;
            _value = value;
        }
        
        int JoyHatControl::JoyID() const 
        {
            return _joyId;
        }
        
        int JoyHatControl::HatID() const 
        {
            return _hatId;
        }
        
        std::string JoyHatControl::ToString() const
        {
            std::ostringstream oss;
            oss << "joy " << _joyId << " hat " << _hatId;
            
            return oss.str();
        }

        int JoyHatControl::LastValue() const 
        {
            return _lastValue;
        }
        
        
        //axis
        
        JoyAxisControl::JoyAxisControl(int joyId, int axisId): _joyId(joyId), _axisId(axisId), _value(0), _lastValue(0)
        {
            
        }
        
                
        int JoyAxisControl::Value() const
        {
            return _value;
        }

        void JoyAxisControl::Value(int value)
        {
            _value = value;
        }

        int JoyAxisControl::JoyID() const
        {
            return _joyId;
        }
        
        int JoyAxisControl::AxisID() const
        {
            return _axisId;
        }

        int JoyAxisControl::LastValue() const
        {
            return _lastValue;
        }

        std::string JoyAxisControl::ToString() const
        {
            std::ostringstream oss;
            oss << "joy " << _joyId << " axis " << _axisId;
            
            return oss.str();
        }

    }
}

