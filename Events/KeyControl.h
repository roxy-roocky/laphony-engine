/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */
/* 
 * File:   KeyControl.h
 * Author: nathan
 *
 * Created on June 22, 2019, 10:11 AM
 */

#ifndef KEYCONTROL_H
#define KEYCONTROL_H

#include "Control.h"

namespace Laphony
{
    namespace Events
    {
            /**
         * \brief Control representing a keyboard key.
         */
        class KeyControl: public Control
        {
            public:
                /**
                 * Return alltime the same type.
                 * @return Control::KEY
                 */
                virtual Control::Type IsType() const {return Control::KEY;}
                
                /**
                 * 
                 * @param keyName The name of the key as a string
                 * Exemples of name: \n
                 * "a" -> A key (whatever the keyboard mapping) \n
                 * "f2" -> F2 key \n
                 * "left" -> Left arrow                  
                 */
                KeyControl(std::string const& keyName);
                /**
                 * Get the current state of the key.
                 * @return 1 if pressed, 0 if released
                 */
                virtual int Value() const;
                /**
                 * Set the value of the control. Use by Events::Engine
                 * @param value New value of the control as int
                 */
                virtual void Value(int value);
                
                /**
                 * Get the key name passed in constructor
                 * @return the key name as string
                 */
                std::string KeyName() const;
                
                virtual int LastState() const override;
                
                virtual std::string ToString() const;
                
                
            private:
                std::string _keyName;
                bool _isPressed;
                
                bool _lastState;
        };
    }
}

#endif /* KEYCONTROL_H */

