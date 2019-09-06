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
                
                Point ComputeRealCenter() const;
                int ComputeRealRadius() const;
                
                virtual Type GetType() const {return Type::CIRCLE;}
            
                virtual bool CollisionWith(Collider* collider) override;
            
            protected:
                virtual bool CheckCollision(BoxCollider* collider) override;
                virtual bool CheckCollision(CircleCollider* collider) override;
                
                Point _center;
                int _radius;

        };
    }
}

#endif /* CIRCLECOLLIDER_H */

