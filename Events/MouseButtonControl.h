/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MouseButtonControl.h
 * Author: nathan
 *
 * Created on September 18, 2019, 9:13 AM
 */

#ifndef MOUSEBUTTONCONTROL_H
#define MOUSEBUTTONCONTROL_H

#include <SDL2/SDL_mouse.h>

#include "Control.h"

namespace Laphony
{
    namespace Events
    {
        class MouseButtonControl: public Control
        {
            public: enum Button
            {
                LEFT = SDL_BUTTON_LEFT,
                MIDDLE = SDL_BUTTON_MIDDLE,
                RIGHT = SDL_BUTTON_RIGHT
            };
            
            public:
                MouseButtonControl(Button const& button);
               /**
                * Get the current value of the control
                * @return Current value of the control as int
                */
               virtual int Value() const;

               virtual void Value(int value);

               /**
                * Get the type of the control. 
                * @return Type of the control. Define by the derivated class.
                */
               virtual Type IsType() const {return Control::MOUSE_BUTTON;};

               virtual int LastValue() const;

               virtual std::string ToString() const;
               
               Button GetButton() const;
            
            private:
                Button _button;
                bool _isPressed;
                
                bool _lastState;

        };
    }
}

#endif /* MOUSEBUTTONCONTROL_H */

