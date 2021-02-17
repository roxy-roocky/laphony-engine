/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Displayable.h
 * Author: Nathan Baumann
 *
 * Created on 21 mars 2019, 00:49
 */

#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

namespace Laphony
{
    namespace Graphics
    {
        class Engine;
        
        class Displayable 
        {
            public:
                Displayable(): _visible(true) {}
                virtual void Display(Engine* engine) = 0;
                
                virtual bool Visible() const {return _visible;}
                virtual void Visible(bool visible) {_visible = visible;}
                
        private:
            bool _visible;

        };
    }
}

#endif /* DISPLAYABLE_H */

