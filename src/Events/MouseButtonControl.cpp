/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MouseButtonControl.cpp
 * Author: nathan
 * 
 * Created on September 18, 2019, 9:13 AM
 */

#include "MouseButtonControl.h"

namespace Laphony
{
    namespace Events
    {

        MouseButtonControl::MouseButtonControl(const Button& button): _button(button), _isPressed(false), _lastState(false)
        {

        }
        
        MouseButtonControl::Button MouseButtonControl::GetButton() const
        {
            return _button;
        }
        
        int MouseButtonControl::LastValue() const
        {
            return static_cast<int>(_lastState);
        }
        
        int MouseButtonControl::Value() const
        {
            return static_cast<int>(_isPressed);
        }
        
        void MouseButtonControl::Value(int value)
        {
            _lastState = _isPressed;
            _isPressed = static_cast<bool>(value);
        }
        
        std::string MouseButtonControl::ToString() const
        {
            return "Mouse Button " + std::string(_button == LEFT?"Left":(_button == MIDDLE?"Middle":"Right"));
        }

    }
}

