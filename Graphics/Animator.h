/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   Graphics/Animator.h
 * \author Nathan Baumann
 *
 * \date June 12, 2019, 8:22 PM
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
        
        /**
         * \brief Represents a set of Animations identified with keys
         */
        class Animator: public virtual Transformable, public virtual Frames::Updatable, public virtual Displayable
        {
            /**
             * \brief Represents a empty key
             */
            public: static const std::string NONE;
            public:
                /**
                 * Default constructor
                 */
                Animator();
                
                /**
                 * Destructor which release all animations marked autofree 
                 */
                virtual ~Animator();
                
                /**
                 * Register an animation with a key
                 * @param name The name (key) of the animation. Use for switch to this animation
                 * @param anim A pointer to the animation
                 * @param autofree True if the animation must be free by the Animator destroyer
                 */
                void Register(std::string name, Animation* anim, bool autofree);
                
                /**
                 * Unregister the animation with the specified name
                 * @param name Name (key) of the animation to unregister
                 * 
                 * The unregistered animation is automatically freed if is marked as autofree
                 */
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

