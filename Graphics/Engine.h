/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Graphics/Engine.h
 * Author: Nathan Baumann
 *
 * Created on 20 mars 2019, 21:33
 */

#ifndef LAPHONY_GRAPHICS_ENGINE_H
#define LAPHONY_GRAPHICS_ENGINE_H

#include <string>
#include <list>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "../Structs.h"
#include "Displayable.h"
#include "../Frames/Updatable.h"

namespace Laphony
{
    namespace Graphics
    {
        class Surface;
        class Displayable;

        typedef SDL_Color Color;
        bool operator==(Color& c1, Color& c2);

        class Engine: public virtual Frames::Updatable
        {
            public:
                Engine(std::string const& title, int w, int h, bool resizable, bool fixedSize);
                Engine(std::string const& title, int w, int h, bool resizable, bool fixedSize, Rect const& camera);
                virtual ~Engine();

                Surface* CreateSurface(std::string const& filename);
                Surface* CreateSurface(int w, int h, Color const& color);

                void Refresh();
                void Clear();
                
                virtual void Update() override;
                
                SDL_Renderer* Renderer();
                SDL_Window* Window();
                
                Rect Camera() const;
                void Camera(Rect camera);
                
                void Register(Displayable* displayable,  bool foreground = false);
                void Unregister(Displayable* displayable);
                
                /**
                 * Transform point from screen to viewport dimension
                 * @param p The point from screen
                 * @return The corresponding point in viewport dimension
                 */
                Point ScreenToViewport(Point const& p) const;
                
                /**
                 * Transform point from viewport to screen dimension
                 * @param p The point from viewport
                 * @return The corresponding point in screen dimension
                 */
                Point ViewportToScreen(Point const& p) const;
                
            private:
                SDL_Window* _window;
                SDL_Renderer* _renderer;
                
                Rect _camera;
                
                std::list<Displayable*> _displayables;
        };
    }
}

#endif /* ENGINE_H */

