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

#include "../Transformable.h"

#include "./Engine.h"

namespace Laphony
{
    namespace Graphics
    {
        class Image: public virtual Displayable, public virtual Transformable
        {
            private:
                class Surface 
                {
                    public:
                        Surface(Engine* engine, SDL_Surface* surface);
                        Surface(Surface const& o);
                        Surface(Surface const& o, Rect const& rect);
                        virtual ~Surface();

                        bool Blit(Rect const& rect, Point pivot, double angle = 0, Rect const& srcRect = {-1});
                        bool Blit(Point const& point, Point pivot, double angle = 0, Rect const& srcRect = {-1});

                        Rect Size() const;

                        uint8_t Alpha() const;
                        void Alpha(uint8_t alpha);

                    private:
                        SDL_Surface* _surface;
                        SDL_Texture* _texture;
                        Engine* _engine;
                };
                
            protected:
                Surface* _surface;
                Rect _srcRect;
                Point _pivot;
                
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
                
                 /**
                * Set the pivot point
                * @param pivot new pivot as Point(x, y)
                */
               virtual void Pivot(Point const& pivot);
               
               /**
             * \brief Get the current center point
             * @return Point with current pivot
             */
            virtual Point Pivot() const;

        };
    }
}

#endif /* IMAGE_H */

