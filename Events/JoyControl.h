/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */
/* 
 * File:   JoyControl.h
 * Author: nathan
 *
 * Created on June 22, 2019, 10:17 AM
 */

#ifndef JOYCONTROL_H
#define JOYCONTROL_H

#include "Control.h"

namespace Laphony
{
    namespace Events
    {
        /**
         * \brief Represent a button from a joystick 
         */
        class JoyButtonControl: public Control
        {
            public:
                /**
                 * Return alltime the same type.
                 * @return Control::JOY_BUTTON
                 */
                virtual Control::Type IsType() const {return Control::JOY_BUTTON;}
                
                /**
                 * 
                 * @param                 
                 */
                JoyButtonControl(int joyID, int buttonID);
                /**
                 * Get the current state of the key.
                 * @return 1 if pressed, 0 if released
                 */
                virtual int Value() const override;
                /**
                 * Set the value of the control. Use by Events::Engine
                 * @param value New value of the control as int
                 */
                virtual void Value(int value) override;
                
                int JoyID() const;
                int ButtonID() const;
                
                virtual int LastValue() const override;
                
                virtual std::string ToString() const override;

                
            private:
                int _joyId, _buttonId;
                bool _isPressed;
                
                bool _lastState;
        };
        
        
        class JoyHatControl: public Control
        {
            public: enum
                    {
                        CENTER = SDL_HAT_CENTERED,
                        UP = SDL_HAT_UP,
                        RIGHT = SDL_HAT_RIGHT,
                        DOWN = SDL_HAT_DOWN,
                        LEFT = SDL_HAT_LEFT,
                        RIGHTUP = SDL_HAT_RIGHTUP,
                        RIGHTDOWN = SDL_HAT_RIGHTDOWN,
                        LEFTUP = SDL_HAT_LEFTUP,
                        LEFTDOWN = SDL_HAT_LEFTDOWN
                    };
            
            public:
                JoyHatControl(int joyID, int hatID);
                
                virtual Control::Type IsType() const {return Control::JOY_HAT;}
                
                virtual int Value() const override;
                
                virtual void Value(int value) override;
                
                int JoyID() const;
                int HatID() const;
                
                virtual int LastValue() const;
                
                virtual std::string ToString() const override;
                
            
            private:
                int _joyId, _hatId;
                int _value;

                int _lastValue;
        };
    }
}

#endif /* JOYCONTROL_H */

