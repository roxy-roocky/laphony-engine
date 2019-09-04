/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   BasicPhysic/MultiCollider.h
 * \author Nathan Baumann
 *
 * \date  September 2, 2019, 10:12 PM
 */

#ifndef MULTICOLLIDER_H
#define MULTICOLLIDER_H

#include <list>
#include "Collider.h"
namespace Laphony
{
    namespace BasicPhysic
    {
        class MultiCollider: public virtual Collider
        {
            public:
                MultiCollider(std::string const& tag);

                virtual Type GetType() const {return Type::MULTIPLE;}
                
                virtual bool CollisionWith(Collider* collider) = 0;
            
            protected:
                virtual bool CheckCollision(BoxCollider* collider) const;
                virtual bool CheckCollision(CircleCollider* collider) const;
                virtual bool CheckCollision(MultiCollider* collider) const;
                
                
                std::list<Collider*> _colliders;
        };
    }
}

#endif /* MULTICOLLIDER_H */

