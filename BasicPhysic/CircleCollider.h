/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   BasicPhysic/CircleCollider.h
 * \author Nathan Baumann
 *
 * \date September 2, 2019, 10:52 PM
 */

#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Collider.h"

namespace Laphony
{
    namespace BasicPhysic
    {

        class CircleCollider: public virtual Collider
        {
            public:
                CircleCollider(std::string const& tag);
                
                virtual Type GetType() const {return Type::CIRCLE;}
            
            private:
                virtual bool CheckCollision(BoxCollider* collider) const = 0;
                virtual bool CheckCollision(CircleCollider* collider) const = 0;
                virtual bool CheckCollision(MultiBoxesCollider* collider) const = 0;

        };
    }
}

#endif /* CIRCLECOLLIDER_H */

