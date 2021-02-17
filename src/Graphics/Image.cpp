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
                
        Image::Image(std::string const& filename, Engine* engine, Rect const& srcRect): Transformable(), _surface(engine->CreateSurface(filename)), _srcRect(srcRect)
        {
            if(_surface)
                _pivot = {_surface->Size().w/2.0, _surface->Size().h/2.0};
        
        }
        
        Image::Image(int w, int h, Color const& color, Engine* engine, Rect const& srcRect): Transformable(), _surface(engine->CreateSurface(w, h,color)), _srcRect(srcRect)
        { 
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

        
    }
}

