/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Graphics/Animator.h
 * Author: Nathan Baumann
 *
 * Created on June 12, 2019, 8:22 PM
 */

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <map>
#include <string>

#include "../Transformable.h"
#include "../Frames/Updatable.h"
#include "Displayable.h"

namespace Laphony
{
    namespace Graphics
    {
        class Animation;
        
        class Animator: public virtual Transformable, public virtual Frames::Updatable, public virtual Displayable
        {
            public: static const std::string NONE;
            public:
                Animator();
                
                virtual ~Animator();
                
                void Register(std::string name, Animation* anim, bool autofree);
                void Unregister(std::string name);
                
                Animation* AnimationFromName(std::string name);
                
                std::string NameFromAnimation(Animation* anim);
                
                std::string CurrentAnimationName();
                void SetCurrentAnimation(std::string name);
                
                virtual void Update() override;
                virtual void Display(Engine* engine) override;
                
            private:
                struct AnimationInfos
                {
                    Animation* anim;
                    bool autofree;
                };
                
                std::map<std::string, AnimationInfos> _animations;
                
                double _speed;
                
                std::string _currentAnimation;
                Animation* _currentAnimationPtr;

        };
    }
}

#endif /* ANIMATOR_H */

