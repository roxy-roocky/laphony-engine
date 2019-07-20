/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Graphics/Animator.cpp
 * Author: Nathan Baumann
 * 
 * Created on June 12, 2019, 8:22 PM
 */

#include <iostream>
#include <algorithm>

#include "Animator.h"

#include "Animation.h"

namespace Laphony
{
    namespace Graphics
    {
        const std::string Animator::NONE = "";
        
        Animator::Animator():Transformable(), Updatable(), _speed(1.0), _currentAnimation(NONE), _currentAnimationPtr(nullptr)
        {
            
        }
        
        Animator::~Animator()
        {
            for(std::map<std::string, AnimationInfos>::iterator it = _animations.begin(); it != _animations.end(); ++it)
                if(it->second.autofree && it->second.anim)
                    delete it->second.anim;
        }
        
        void Animator::Register(std::string name, Animation* anim, bool autofree)
        {
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            _animations[name] = AnimationInfos{anim, autofree};
        }
        
        void Animator::Unregister(std::string name)
        {
            try
            {
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
               AnimationInfos& anim = _animations.at(name);
               _animations.erase(name);
               
               if(anim.autofree && anim.anim)
                    delete anim.anim;
               
            }
            catch(std::exception ex)
            {
                
            }
        }
        
        Animation* Animator::AnimationFromName(std::string  name)
        {
            try
            {
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
               AnimationInfos& anim = _animations.at(name);
               
               return anim.anim;
               
            }
            catch(std::exception ex)
            {
                return nullptr;
            }
        }
        
        std::string Animator::NameFromAnimation(Animation* anim)
        {
            for(std::map<std::string, AnimationInfos>::iterator it = _animations.begin(); it != _animations.end(); ++it)
            {
                if(it->second.anim == anim)
                    return it->first;
            }
            
            return NONE;
        }
        
        std::string Animator::CurrentAnimationName()
        {
            return _currentAnimation;
        }
        
        void Animator::SetCurrentAnimation(std::string name)
        {
            try
            {
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                
                
                if(name == _currentAnimation)
                    return;
                
               AnimationInfos& anim = _animations.at(name);
               
               _currentAnimation = name;
               _currentAnimationPtr = anim.anim;
               
               _currentAnimationPtr->Rewind();
               
               if(!anim.anim)
               {
                   throw std::exception{};
               }
               
            }
            catch(std::exception ex)
            {
                _currentAnimationPtr = nullptr;
                _currentAnimation = NONE;
            }
        }
        
        void Animator::Update()
        {
            if(_currentAnimationPtr)
            {
                _currentAnimationPtr->Update();
            }
        }
        
        void Animator::Display(Engine* engine)
        {
            if(_currentAnimationPtr)
            {
                Transformable oldAnimTransform = *_currentAnimationPtr;
                static_cast<Transformable*>(_currentAnimationPtr)->operator+=(*this);
                
                _currentAnimationPtr->Display(engine);
                
                static_cast<Transformable*>(_currentAnimationPtr)->operator=(oldAnimTransform);
            }
        }
    }
}

