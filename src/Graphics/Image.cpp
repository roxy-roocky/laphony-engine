/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Image.cpp
 * Author: Nathan Baumann
 * 
 * Created on 21 mars 2019, 11:15
 */

#include "Image.h"

namespace Laphony
{
    namespace Graphics
    {
        Image::Image(Image const& orig): Transformable(orig), _surface(new Surface(*orig._surface)), _srcRect(orig._srcRect)
        {
            if(_surface)
                _pivot = {_surface->Size().w/2.0, _surface->Size().h/2.0};
        }
        
        Image::Image(Image const& orig, Rect const& rect):Transformable(orig), _surface(new Surface(*orig._surface, rect)), _srcRect(orig._srcRect)
        {
            if(_surface)
                _pivot = {_surface->Size().w/2.0, _surface->Size().h/2.0};
        }
                
        Image::Image(std::string const& filename, Engine* engine, Rect const& srcRect): Transformable(), _surface(new Surface(engine, IMG_Load(filename.c_str()))), _srcRect(srcRect)
        {
            if(_surface)
                _pivot = {_surface->Size().w/2.0, _surface->Size().h/2.0};
        
        }
        
        Image::Image(int w, int h, Color const& color, Engine* engine, Rect const& srcRect): Transformable(), _surface(nullptr), _srcRect(srcRect)
        { 
            SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0,0,0,0);
            SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, color.r, color.g, color.b));
            _surface = new Surface(engine, surface);
            
            if(_surface)
                _pivot = {_surface->Size().w/2.0, _surface->Size().h/2.0};
        }
        
        Image::~Image()
        {
            if(_surface)
                delete _surface;
        }

        void Image::Display(Engine* engine)
        {
            if(_surface)
            {
               double realW = 0;
               double realH = 0;
               Point pivot = _pivot;
               
               if(_srcRect.x > -1)
               {
                  realW = _srcRect.w * Scale().x;
                  realH = _srcRect.h * Scale().y; 
                  
                  
               }
               else
               {
                   realW = _surface->Size().w * Scale().x;
                   realH = _surface->Size().h * Scale().y;
                
               }
               
               
               pivot.x *= std::abs(Scale().x);
               pivot.y *= std::abs(Scale().y);
               
               _surface->Blit(Laphony::Rect{Position().x, Position().y, realW, realH}, pivot,Angle(), _srcRect);
            }
           
                
        }
        
        Rect Image::Size() const
        {
            if(_surface)
                return _surface->Size();
            else
                return {-1};
        }
        
        Rect Image::SrcRect() const
        {
            return _srcRect;
        }
        void Image::SrcRect(Rect const& srcRect)
        {
            if(srcRect.x < 0 || srcRect.y < 0)
                _srcRect = {-1};
            else
                _srcRect = srcRect;
        }
        
        uint8_t Image::Alpha() const
        {
            if(_surface)
                return _surface->Alpha();
            else
                return 0;
        }
        
        void Image::Alpha(uint8_t alpha)
        {
            if(_surface)
                _surface->Alpha(alpha);
        }
        
        Point Image::Pivot() const {return {std::round(Pivot().x * std::abs(Scale().x)), std::round(_pivot.y * std::abs(Scale().y))};}
        
        void Image::Pivot(Point const& pivot)
        {
            _pivot = pivot;
        }
        
        
        Image::Surface::Surface(Engine* engine, SDL_Surface* surface): _surface(surface), _texture(SDL_CreateTextureFromSurface(engine->Renderer(), surface)), _engine(engine)
        { 
            SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
        }

        Image::Surface::Surface(Surface const& o): _surface(SDL_ConvertSurface(o._surface, o._surface->format,o._surface->flags)), _texture(SDL_CreateTextureFromSurface(o._engine->Renderer(), _surface)), _engine(o._engine)
        { 
            SDL_SetTextureAlphaMod(_texture, SDL_BLENDMODE_BLEND);
        }
        
        Image::Surface::Surface(Surface const& o, Rect const& rect): _engine(o._engine)
        {
            SDL_Rect sdlRect = {static_cast<int>(std::round(rect.x)), static_cast<int>(std::round(rect.y)), static_cast<int>(std::round(rect.w)), static_cast<int>(std::round(rect.h))};
            
            _surface = SDL_CreateRGBSurface(0, sdlRect.w, sdlRect.h, 32, 0,0,0,0);
            SDL_BlitSurface(o._surface, &sdlRect, _surface, nullptr);
            
            _texture = SDL_CreateTextureFromSurface(o._engine->Renderer(), _surface);
            
            SDL_SetTextureAlphaMod(_texture, SDL_BLENDMODE_BLEND);
        }

        Image::Surface::~Surface()
        {
            if(_surface)
                SDL_FreeSurface(_surface);

            if(_texture)
                SDL_DestroyTexture(_texture);
        }


        bool Image::Surface::Blit(const Point& point, Point pivot, double angle, Rect const& srcRect)
        {
            return Blit({point.x, point.y, static_cast<double>(_surface->w), static_cast<double>(_surface->h)}, pivot, angle, srcRect);
        }


        bool Image::Surface::Blit(const Rect& rect, Point  pivot, double angle, Rect const& srcRect) 
        {
            
            Rect camera = _engine->Camera();
            
            if(pivot.x < 0)
            {
                pivot.x = std::abs(rect.w)/2;
                pivot.y = std::abs(rect.h)/2;
            }
            
            SDL_Rect realRect = {static_cast<int>(std::round(rect.x - pivot.x)), static_cast<int>(std::round(rect.y - pivot.y)), static_cast<int>(std::abs(std::round(rect.w))), static_cast<int>(std::abs(std::round(rect.h)))};
            
            realRect.x -= camera.x;
            realRect.y -= camera.y;

            
            SDL_RendererFlip flip = static_cast<SDL_RendererFlip>((rect.w < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | (rect.h < 0 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE));
            
            //std::cout << pivot.x << ";" << pivot.y << "\n";
            
            SDL_Point sdlPivot = {static_cast<int>(std::round(pivot.x)), static_cast<int>(std::round(pivot.y))};
            SDL_Rect sdlRealDest = {static_cast<int>(std::round(realRect.x)), static_cast<int>(std::round(realRect.y)),static_cast<int>(std::round(realRect.w)), static_cast<int>(std::round(realRect.h))};
            
            if(srcRect.x == -1)
            {
                
                return SDL_RenderCopyEx(_engine->Renderer(), _texture, nullptr, &sdlRealDest, angle, &sdlPivot, flip) == 0;
            }
            else
            {   
                SDL_Rect sdlSrcRect = {static_cast<int>(std::round(srcRect.x)), static_cast<int>(std::round(srcRect.y)), static_cast<int>(std::round(srcRect.w)), static_cast<int>(std::round(srcRect.h))};
                return SDL_RenderCopyEx(_engine->Renderer(), _texture, &sdlSrcRect, &sdlRealDest, angle, &sdlPivot, flip) == 0;
            }
            
            
        }

        Rect Image::Surface::Size() const
        {
            return {0, 0, static_cast<double>(_surface->w), static_cast<double>(_surface->h)};
        }
        
        uint8_t Image::Surface::Alpha() const
        {
            Uint8 alpha = 0;
            if(_texture)
                SDL_GetTextureAlphaMod(_texture, &alpha);
            
            return static_cast<uint8_t>(alpha);
        }
        
        void Image::Surface::Alpha(uint8_t alpha)
        {
            if(_texture)
                SDL_SetTextureAlphaMod(_texture, static_cast<Uint8>(alpha));
        }
        
    }
}

