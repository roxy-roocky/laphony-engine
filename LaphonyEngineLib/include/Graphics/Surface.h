/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */


/** 
 * \file   Surface.h
 * \author Nathan Baumann
 * \brief Represent a base bitmap surface * \date mars 20 2019, 08:57 pm

 * \date mars 20 2019, 08:57 pm
 */

#ifndef SURFACE_H
#define SURFACE_H

#include "Engine.h"

namespace Laphony
{
    namespace Graphics
    {
        class Engine;

        /**
         * \class Surface
         */
        class Surface 
        {
            public:
                Surface(Surface const& o);
                Surface(Surface const& o, Rect const& rect);
                virtual ~Surface();

                bool Blit(Rect const& rect, Point pivot, double angle = 0, Rect const& srcRect = {-1});
                bool Blit(Point const& point, Point pivot, double angle = 0, Rect const& srcRect = {-1});
                
                Rect Size() const;
                
                uint8_t Alpha() const;
                void Alpha(uint8_t alpha);

            private:
                Surface(Engine* engine, SDL_Surface* surface);

                SDL_Surface* _surface;
                SDL_Texture* _texture;
                Engine* _engine;

                friend Engine;
        };
    }
}

#endif /* SURFACE_H */

