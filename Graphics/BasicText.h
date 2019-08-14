/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Graphics/BasicText.h
 * Author: Nathan Baumann
 *
 * Created on 7 avril 2019, 14:27
 */

#ifndef LAPHONY_GRAPHICS_BASICTEXT_H
#define LAPHONY_GRAPHICS_BASICTEXT_H

#include "Engine.h"

#include "../Transformable.h"

namespace Laphony
{
    namespace Graphics
    {
        class BasicText: public virtual Displayable, public virtual Transformable
        {
            public: static const int FONT_SIZE = 8;
            public:
                BasicText(std::string const& text, Point const& position, double renderSize = 1.0, bool isStickOnScreen = false, Color const& colorText = {255,255,255,255}, Color const& colorBackground = {0,0,0,0});
                
                BasicText(const BasicText& orig);
                
                virtual ~BasicText();
                
                virtual void Display(Engine* engine);
                
                std::string Text() const;
                void Text(std::string const& text);
                
                Color ColorText() const;
                void ColorText(Color const& colorText);
                
                Color ColorBackground() const;
                void ColorBackground(Color const& colorBackground);
                
                
                bool IsStickOnScreen() const;
                void IsStickOnScreen(bool isStickOnScreen);
                
                                
                void RenderTextNow(SDL_Renderer* renderer);
                
                
                std::string _text;
                Color _colorText, _colorBackground;
                
                bool _isStickOnScreen;
                
                
                SDL_Texture* _renderedText;
                
                bool _mustBeRender;
                

        };
    }
}


#endif /* BASICTEXT_H */

