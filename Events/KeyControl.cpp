/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */
/* 
 * File:   KeyControl.cpp
 * Author: nathan
 * 
 * Created on June 22, 2019, 10:11 AM
 */

#include "KeyControl.h"

namespace Laphony
{
    namespace Events
    {
        KeyControl::KeyControl(std::string const& keyName): _keyName(keyName), _isPressed(false)
        {
            
        }
        
        int KeyControl::Value() const
        {
            return _isPressed?1:0;
        }
        
        void KeyControl::Value(int value)
        {
            _lastState = _isPressed;
            _isPressed = static_cast<bool>(value);
        }
        
        std::string KeyControl::KeyName() const
        {
            return _keyName;
        }
        
        int KeyControl::LastValue() const
        {
            return _lastState;
        }
        
        std::string KeyControl::ToString() const
        {
            return _keyName;
        }
        
        void KeyControl::Update()
        {
            const Uint8* keys = SDL_GetKeyboardState(nullptr);
            
            _isPressed = keys[SDL_GetScancodeFromKey(SDL_GetKeyFromName(_keyName.c_str()))];
        }
    }
}

