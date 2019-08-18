/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Image.h
 * Author: Nathan
 *
 * Created on 21 mars 2019, 11:15
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "Surface.h"

#include "../Transformable.h"

namespace Laphony
{
    namespace Graphics
    {
        class Image: public virtual Displayable, public virtual Transformable
        {
            //TODO: std::map<SDL_Texture*> for multi context image 
            protected:
                Surface* _surface;
                Rect _srcRect;
                
            public:
                Image(std::string const& filename, Engine* engine, Rect const& srcRect = {-1});
                Image(int w, int h, Color const& color, Engine* engine, Rect const& srcRect = {-1});
                
                Image(Image const& orig); 
                Image(Image const& orig, Rect const& rect);
                
                ~Image();
                
                Rect Size() const;
                
                Rect SrcRect() const;
                void SrcRect(Rect const& srcRect);
                
                uint8_t Alpha() const;
                void Alpha(uint8_t alpha);
                
                virtual void Display(Engine* engine);
               
        };
    }
}

#endif /* IMAGE_H */

