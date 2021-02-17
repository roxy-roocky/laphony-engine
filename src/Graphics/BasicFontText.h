/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BasicFontText.h
 * Author: nathan
 *
 * Created on December 6, 2019, 8:56 AM
 */

#ifndef BASICFONTTEXT_H
#define BASICFONTTEXT_H

#include "BasicText.h"

#include <map>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace Laphony
{
    namespace Graphics
    {
        class BasicFontText: public BasicText
        {
            protected:
                static int _countOfInstances;
                
                static std::map<std::pair<std::string,int>, TTF_Font*> _fonts;
                
                
                int _sizePoint;
                TTF_Font* _fontPtr;
                
                virtual void RenderTextNow(SDL_Renderer* renderer) override;
            
            public:
                BasicFontText(std::string const& fontFile, std::string const& text, Point const& position, int sizePoint = 12, bool isStickOnScreen = false, Color const& colorText = {255,255,255,255}, Color const& colorBackground = {0,0,0,0});
                
                virtual ~BasicFontText();
        };
    }
}

#endif /* BASICFONTTEXT_H */

