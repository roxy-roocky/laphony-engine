/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Engine.cpp
 * Author: Nathan
 * 
 * Created on 20 mars 2019, 21:33
 */

#include "Engine.h"

#include "Surface.h"
#include "Displayable.h"

namespace Laphony
{
    namespace Graphics
    {
        bool operator==(Color& c1, Color& c2)
        {
            return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
        };
        
        Engine::Engine(std::string const& title, int w, int h, bool resizable, bool fixedSize): Engine::Engine(title, w, h, resizable, fixedSize, Rect{0,0,w,h})
        {
            
        }
        
        Engine::Engine(std::string const& title, int w, int h, bool resizable, bool fixedSize, Rect const& camera): _camera(camera)
        {
            if(!SDL_WasInit(0))
            {
                SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC);
                IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF|IMG_INIT_WEBP);
                
                atexit(SDL_Quit);
                atexit(IMG_Quit);
            }

            _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN | resizable?SDL_WINDOW_RESIZABLE:0);

            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
            //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
            
            if(fixedSize)
                SDL_RenderSetLogicalSize(_renderer, w, h);
        }


        Surface* Engine::CreateSurface(const std::string& filename) 
        {
            return new Surface(this, IMG_Load(filename.c_str()));
        }


        Surface* Engine::CreateSurface(int w, int h, const Color& color)
        {
            SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0,0,0,0);
            SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, color.r, color.g, color.b));
            return new Surface(this, surface);
        }


        void Engine::Refresh()
        {
            SDL_RenderPresent(_renderer);
        }


        void Engine::Clear()
        {
            //SDL_SetRenderDrawColor(_renderer,0,0,0,255);
            SDL_RenderClear(_renderer);
        }


        Engine::~Engine()
        {
            if(_renderer)
                SDL_DestroyRenderer(_renderer);

            if(_window)
                SDL_DestroyWindow(_window);
        }
        
        SDL_Renderer* Engine::Renderer(){ return _renderer; }
        SDL_Window* Engine::Window(){ return _window; }
        
        Rect Engine::Camera() const {return _camera;}
        
        void Engine::Camera(Rect camera)
        {
            if(camera.x < 0)
                camera.x = 0;
            if(camera.y < 0)
                camera.y = 0;
            
            _camera = camera;
        }
        
        
        void Engine::Register(Displayable* displayable, bool foreground)
        {
            if(foreground)
                _displayables.push_back(displayable);
            else
                _displayables.push_front(displayable);
        }
        
        
        void Engine::Unregister(Displayable* displayable)
        {
            _displayables.remove(displayable);
        }
        
        
        void Engine::Update()
        {
            Clear();
            
            for(Displayable* d: _displayables)
                if(d && d->Visible())
                    d->Display(this);
            
            Refresh();
        }

    }
}

