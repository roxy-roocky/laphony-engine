/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   BasicPhysic/Collider.h
 * \author Nathan Baumann
 *
 * \date august 29 2019, 5:19 PM
 */

#ifndef COLLIDER_H
#define COLLIDER_H

#include <string>
#include "../Transformable.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        class BoxCollider;
        class CircleCollider;
        class MultiBoxesCollider;
        
        class Collider: public virtual Transformable
        {
            public: enum Type
            {
                BOX,
                CIRCLE,
                MULTIPLEBOXES
            };
            
            private:
                std::string _tag;
                
            public:
                Collider(std::string const& tag);
                
                std::string GetTag() const;
                void SetTag();
                
                bool CollisionWith(Collider* collider) const;
                
                virtual Type GetType() const = 0;
            
            private:
                virtual bool CheckCollision(BoxCollider* collider) const = 0;
                virtual bool CheckCollision(CircleCollider* collider) const = 0;
                virtual bool CheckCollision(MultiBoxesCollider* collider) const = 0;
        };
    }
}

#endif /* COLLIDER_H */

