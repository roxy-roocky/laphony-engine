/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Graphics/BasicText.cpp
 * Author: Nathan
 * 
 * Created on 7 avril 2019, 14:27
 */

#include "BasicText.h"

#include <SDL2/SDL2_gfxPrimitives.h>

namespace Laphony
{
    namespace Graphics
    {
        
        BasicText::BasicText(std::string const& text, Point const& position,double renderSize, bool isStickOnScreen, Color const& colorText, Color const& colorBackground): Transformable(), _text(text),  _isStickOnScreen(isStickOnScreen), _colorBackground(colorBackground), _colorText(colorText), _renderedText(nullptr), _mustBeRender(true)
        { 
            Scale({renderSize, renderSize});
            Position(position);
        }
        
        BasicText::BasicText(const BasicText& orig) {

        }

                
        BasicText::~BasicText()
        {
            if(_renderedText)
                SDL_DestroyTexture(_renderedText);
        }
        //BasicText::BasicText(const BasicText& orig);
        //virtual BasicText::~BasicText();
        
        void BasicText::RenderTextNow(SDL_Renderer* renderer)
        {
            if(_renderedText)
                SDL_DestroyTexture(_renderedText);
            
            _renderedText = nullptr;
            
            SDL_Surface* renderSurface = SDL_CreateRGBSurface(0, FONT_SIZE*_text.size(), FONT_SIZE, 32, 0,0,0,0);
            const char* err = SDL_GetError();
            SDL_Renderer* rendererText = SDL_CreateSoftwareRenderer(renderSurface);
            
            SDL_SetRenderDrawBlendMode(rendererText, SDL_BLENDMODE_BLEND);
            
            
            if(_colorBackground.a == 0)
            {
                if(_colorBackground == _colorText)
                    _colorBackground.r = _colorText.r - 10;
                
                SDL_SetColorKey(renderSurface, 1, SDL_MapRGB(renderSurface->format, _colorBackground.r, _colorBackground.g, _colorBackground.b));
            }
            
            
            SDL_SetRenderDrawColor(rendererText, _colorBackground.r, _colorBackground.g, _colorBackground.b, 255);
            
            
            SDL_RenderClear(rendererText);

            gfxPrimitivesSetFont(nullptr,8,8);//RESET FUCKING CHAR RENDER CACHE (3 hours bug!!!!!!!!!!!!!)
            stringRGBA(rendererText, 0, 0, _text.c_str(), _colorText.r, _colorText.g, _colorText.b, 255);
            
            SDL_RenderPresent(rendererText);

            
            _renderedText = SDL_CreateTextureFromSurface(renderer, renderSurface);
            
            SDL_SetTextureBlendMode(_renderedText, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(_renderedText, _colorText.a);
            
            err = SDL_GetError();
            
            SDL_DestroyRenderer(rendererText);
            SDL_FreeSurface(renderSurface);
          
            _mustBeRender = false;
        }

        void BasicText::Display(Engine* engine)
        {           
            if(engine)
            {
                if(_mustBeRender)
                    RenderTextNow(engine->Renderer());
                
                int w, h;
                SDL_QueryTexture(_renderedText, nullptr, nullptr, &w, &h);
                
                Point pivot = _pivot;
                Rect dest = {Position().x, Position().y, w*Scale().x, h*Scale().y};
                
                if(pivot.x < 0)
                {
                    pivot.x = std::abs(dest.w)/2;
                    pivot.y = std::abs(dest.h)/2;
                }
                 
                dest.x -= pivot.x;
                dest.y -= pivot.y;
                
                
                if(!_isStickOnScreen)
                {
                    Rect camera = engine->Camera();
                    dest.x -= camera.x;
                    dest.y -= camera.y;
                }
                
                SDL_Point sdlPivot = {static_cast<int>(std::round(pivot.x)), static_cast<int>(std::round(pivot.y))};
                SDL_Rect sdlDest = {static_cast<int>(std::round(dest.x)), static_cast<int>(std::round(dest.y)), static_cast<int>(std::round(dest.w)), static_cast<int>(std::round(dest.h))};
                SDL_RenderCopyEx(engine->Renderer(), _renderedText, nullptr, &sdlDest, Angle(), &sdlPivot, SDL_FLIP_NONE);
            }
        }

        std::string BasicText::Text() const
        {
            return _text;
        }
        void BasicText::Text(std::string const& text)
        {
            _text = text;
            _mustBeRender = true;
        }

        Color BasicText::ColorText() const
        {
            return _colorText;
        }
        void BasicText::ColorText(Color const& colorText)
        {
            _colorText = colorText;
            _mustBeRender = true;
        }

        Color BasicText::ColorBackground() const
        {
            return _colorBackground;
        }
        void BasicText::ColorBackground(Color const& colorBackground)
        {
            _colorBackground = colorBackground;
            _mustBeRender = true;
        }

        bool BasicText::IsStickOnScreen() const
        {
            return _isStickOnScreen;
        }
        void BasicText::IsStickOnScreen(bool isStickOnScreen)
        {
            _isStickOnScreen = isStickOnScreen;
        }
        
        Point BasicText::GetPivot() const
        {
            return _pivot;
        }
        
        void BasicText::SetPivot(Point const& pivot)
        {
            _pivot = pivot;
        }
    }
}

