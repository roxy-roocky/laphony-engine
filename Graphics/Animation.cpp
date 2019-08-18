/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Graphics/Animation.cpp
 * Author: Nathan Baumann
 * 
 * Created on 24 avril 2019, 14:18
 */

#include <vector>
#include <iostream>

#include "Animation.h"

namespace Laphony
{
    namespace Graphics
    {
        Animation::Animation(Image* image, std::vector<Animation::Frame> frames, bool autofree, bool reverseLoop): Transformable(), _image(image), _frames(frames), _currentFrame(0), _currentTick(0), _reverseLoop(reverseLoop), _reversePlay(false), _speed(1.0), _autofree(autofree)
        {
            
        }
        
        Animation::Animation(Image* image, Rect const& rect, int duration, bool autofree, Point const& pivot, bool reverseLoop): Transformable(), _image(image), _currentFrame(0), _currentTick(0), _reverseLoop(reverseLoop), _reversePlay(false), _speed(1.0), _autofree(autofree)
        {
            if(_image)
            {
                for(int i=0; i<_image->Size().w/rect.w; i++)
                {
                    Rect r = rect;
                    r.x = i*rect.w;
                    _frames.push_back({r, duration, pivot});
                }
                
                if(_reverseLoop)
                {
                    size_t size = _frames.size();
                    for(int i=0; i<size; i++)
                        _frames.push_back(_frames[size-1-i]);
                }
            }
        }
        
        Animation::~Animation()
        {
            if(_autofree && _image)
                delete _image;
        }
        
        void Animation::Display(Engine* engine)
        {
            if(_image)
            {
                _image->SrcRect(_frames[_currentFrame].rect);
                _image->Pivot(_frames[_currentFrame].pivot);
                
                Transformable oldImageTransform = *_image;
                static_cast<Transformable*>(_image)->operator+=(*this);
                
                _image->Display(engine);
                
                static_cast<Transformable*>(_image)->operator=(oldImageTransform);
            }
        }
        
        void Animation::Update()
        {
            if(_reversePlay)
                Backward();
            else
                Forward();
        }
        
        bool Animation::Forward()
        {
            bool ended = false;
            _currentTick += _speed;
           
            if(_currentTick > _frames[_currentFrame].duration)
            {
                _currentTick = 0;
                _currentFrame++;
                
                if(_currentFrame >= _frames.size())
                {
                    _currentFrame = 0;
                    ended = true;
                }
            }
           
            
            return ended;
        }
        
        bool Animation::Backward()
        {
            bool ended = false;
            _currentTick -= _speed;
            if(_currentTick < 0)
            {
                _currentTick = _frames[_currentFrame].duration;
                _currentFrame--;
                
                if(_currentFrame < 0)
                {
                    _currentFrame = _frames.size() - 1;
                    ended = true;
                }
            }
            
            return ended;
        }
        
        void Animation::Rewind()
        {
            _currentFrame = _currentTick = 0;
        }
        
        
        void Animation::ReversePlay(bool reverse)
        {
            _reversePlay = reverse;
        }
        
        bool Animation::ReversePlay() const
        {
            return _reversePlay;
        }
        
        double Animation::Speed() const
        {
            return _speed;
        }
        
        void Animation::Speed(double speed)
        {
            if(speed > 0)
                _speed = speed;
        }
        
    }
}

