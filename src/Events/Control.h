/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/**
 * \file  Events/Control.h
 * \author Nathan Baumann
 *
 * \date april 23 2019, 11:04 pm
 */

#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <SDL2/SDL_joystick.h>

namespace Laphony
{
    /**
     * \brief Contains all events relatives classes and fonctions
     */
    namespace Events
    {
        /**
         * \brief Represent a control whatever kind of control.
         */
        class Control
        {
            /**
             * \enum Control::Type
             * \brief Type of controls. Evolve with updates.
             */
            public: enum Type
            {
                KEY             = 0b00000001, /*!< A key from the keyboard */
                
                MOUSE_BUTTON    = 0b00000010, /*!< Button from the mouse */
                
                JOY_BUTTON      = 0b00000100, /*!< Button from the joy */
                JOY_HAT         = 0b00001000, /*!< hat from the joy */
                JOY_BALLAXIS    = 0b00010000, /*!< ball axis from the joy */
                JOY_AXIS        = 0b00100000,  /*!< joystick axis from the joy */
                
                TOUCH           = 0b01000000 /*!< touchscreen event */
            };
                
            public:
                
                virtual ~Control() = default;
                /**
                 * Get the current value of the control
                 * @return Current value of the control as int
                 */
                virtual int Value() const = 0;
                
                virtual void Value(int value) = 0;

                /**
                 * Get the type of the control. 
                 * @return Type of the control. Define by the derivated class.
                 */
                virtual Type IsType() const = 0;
                
                virtual int LastValue() const = 0;
                
                virtual std::string ToString() const = 0;
                
        };
        
    }
}


#endif /* CONTROL_H */

