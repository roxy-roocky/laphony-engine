/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/**
 * \file   Frames/Updatable.h
 * \author Nathan Baumann
 *
 * \date april 4 2019, 07:48 am
 */

#ifndef UPDATABLE_H
#define UPDATABLE_H

namespace Laphony
{
    namespace Frames
    {
        /**
         * \brief Interface. Let you register your object to the frame engine, to be updated automatically.
         */
        class Updatable
        {
            public:
                Updatable(): _paused(false){}
                /**
                 * \brief This method will be called by the frame engine.
                 */
                virtual void Update() = 0;
                
                /**
                 * Check if the object is paused
                 * @return 
                 */
                virtual bool Paused() {return _paused;}
                
                /**
                 * Pause or resume the update of the object
                 * @param pause New pause state of the object
                 */
                virtual void Pause(bool pause) {_paused = pause;}
                
            private:
                bool _paused;

        };
    }
}

#endif /* UPDATABLE_H */

