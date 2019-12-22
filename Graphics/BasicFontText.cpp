/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BasicFontText.cpp
 * Author: nathan
 * 
 * Created on December 6, 2019, 8:56 AM
 */

#include "BasicFontText.h"

int Laphony::Graphics::BasicFontText::_countOfInstances = 0;
std::map<std::pair<std::string,int>, TTF_Font*>  Laphony::Graphics::BasicFontText::_fonts;

Laphony::Graphics::BasicFontText::BasicFontText(std::string const& fontFile, std::string const& text, Point const& position, int sizePoint, bool isStickOnScreen, Color const& colorText, Color const& colorBackground): BasicText(text, position, 1.0, isStickOnScreen, colorText, colorBackground), _sizePoint(sizePoint)
{
    _countOfInstances++;
    
    std::pair<std::string, int> pair(fontFile, sizePoint);
    
    if(_fonts.find(pair) == _fonts.end())
    {
        if(!TTF_WasInit())
        {
            TTF_Init();
            
            atexit(TTF_Quit);
        }
        
        TTF_Font* font = TTF_OpenFont(fontFile.c_str(), sizePoint);
        if(!font)
        {
            std::cerr << "Graphics: Error when load \"" << fontFile << "\": " << TTF_GetError() << std::endl; 
        }
        else
        {
            std::cout << "Graphics: New font loaded : \"" << fontFile << "\" with size " << sizePoint << std::endl; 
            _fonts[pair] = font;
            _fontPtr = font;
        }
    }
    else
        _fontPtr = _fonts[pair];
    
}

Laphony::Graphics::BasicFontText::~BasicFontText()
{
    
    _countOfInstances--;
    
    if(_countOfInstances <= 0)
        for(std::pair<const std::pair<std::string, int>, TTF_Font*> &pair: _fonts)
            TTF_CloseFont(pair.second);
    
    
    if(_renderedText)
        SDL_DestroyTexture(_renderedText);
}

void Laphony::Graphics::BasicFontText::RenderTextNow(SDL_Renderer* renderer)
{
    if(_renderedText)
        SDL_DestroyTexture(_renderedText);

    _renderedText = nullptr;

    SDL_Surface* renderSurface = nullptr;
    if(_colorBackground.a == 0)
        renderSurface = TTF_RenderUTF8_Blended(_fontPtr, _text.c_str(), _colorText);
    else
        renderSurface = TTF_RenderUTF8_Shaded(_fontPtr, _text.c_str(), _colorText, _colorBackground);

    _renderedText = SDL_CreateTextureFromSurface(renderer, renderSurface);

    SDL_SetTextureBlendMode(_renderedText, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(_renderedText, _colorText.a);

    SDL_FreeSurface(renderSurface);

    _mustBeRender = false;
}

