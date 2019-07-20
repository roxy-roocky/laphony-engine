/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Surface.cpp
 * Author: Nathan Baumann
 * 
 * Created on 20 mars 2019, 20:57
 */

#include "Surface.h"
#include "Engine.h"

#include <iostream>

namespace Laphony
{
    namespace Graphics
    {
        Surface::Surface(Engine* engine, SDL_Surface* surface): _surface(surface), _texture(SDL_CreateTextureFromSurface(engine->Renderer(), surface)), _engine(engine)
        { 
            SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
        }

        Surface::Surface(Surface const& o): _surface(SDL_ConvertSurface(o._surface, o._surface->format,o._surface->flags)), _texture(SDL_CreateTextureFromSurface(o._engine->Renderer(), _surface)), _engine(o._engine)
        { 
            SDL_SetTextureAlphaMod(_texture, SDL_BLENDMODE_BLEND);
        }
        
        Surface::Surface(Surface const& o, Rect const& rect): _engine(o._engine)
        {
            _surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0,0,0,0);
            SDL_BlitSurface(o._surface, &rect, _surface, nullptr);
            
            _texture = SDL_CreateTextureFromSurface(o._engine->Renderer(), _surface);
            
            SDL_SetTextureAlphaMod(_texture, SDL_BLENDMODE_BLEND);
        }

        Surface::~Surface()
        {
            if(_surface)
                SDL_FreeSurface(_surface);

            if(_texture)
                SDL_DestroyTexture(_texture);
        }


        bool Surface::Blit(const Point& point, Point pivot, double angle, Rect const& srcRect)
        {
            return Blit({point.x, point.y, _surface->w, _surface->h}, pivot, angle, srcRect);
        }


        bool Surface::Blit(const Rect& rect, Point  pivot, double angle, Rect const& srcRect) 
        {
            
            SDL_Rect camera = _engine->Camera();
            SDL_Rect realRect = {rect.x, rect.y, std::abs(rect.w), std::abs(rect.h)};
            
            realRect.x -= camera.x;
            realRect.y -= camera.y;
            
            if(pivot.x < 0)
            {
                pivot.x = std::abs(rect.w)/2;
                pivot.y = std::abs(rect.h)/2;
            }
            
            realRect.x -=  pivot.x;
            realRect.y -= pivot.y;
            
            SDL_RendererFlip flip = static_cast<SDL_RendererFlip>((rect.w < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | (rect.h < 0 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE));
            
            //std::cout << pivot.x << ";" << pivot.y << "\n";
            
            if(srcRect.x == -1)
            {
                
                return SDL_RenderCopyEx(_engine->Renderer(), _texture, nullptr, &realRect, angle, &pivot, flip) == 0;
            }
            else
            {               
                return SDL_RenderCopyEx(_engine->Renderer(), _texture, &srcRect, &realRect, angle, &pivot, flip) == 0;
            }
            
            
        }

        Rect Surface::Size() const
        {
            return {0, 0, _surface->w, _surface->h};
        }
        
        uint8_t Surface::Alpha() const
        {
            Uint8 alpha = 0;
            if(_texture)
                SDL_GetTextureAlphaMod(_texture, &alpha);
            
            return static_cast<uint8_t>(alpha);
        }
        
        void Surface::Alpha(uint8_t alpha)
        {
            if(_texture)
                SDL_SetTextureAlphaMod(_texture, static_cast<Uint8>(alpha));
        }

    }
}





