/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   BasicPhysic/BoxCollider.h
 * \author Nathan Baumann
 *
 * \date September 2, 2019, 10:42 PM
 */

#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"


namespace Laphony
{
    namespace BasicPhysic
    {
        class BoxCollider: public virtual Collider
        {
            public:
                BoxCollider(std::string const& tag);
                
                Rect ComputeRealBox() const;

                virtual Type GetType() const {return Type::BOX;}
                
                virtual bool CollisionWith(Collider* collider) override;
            
            protected:
                virtual bool CheckCollision(BoxCollider* collider) override;
                virtual bool CheckCollision(CircleCollider* collider) override;
                
                Rect _box;
                
        };
    }
}

#endif /* BOXCOLLIDER_H */

