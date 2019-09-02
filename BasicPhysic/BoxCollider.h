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

                virtual Type GetType() const {return Type::BOX;}
            
            private:
                virtual bool CheckCollision(BoxCollider* collider) const = 0;
                virtual bool CheckCollision(CircleCollider* collider) const = 0;
                virtual bool CheckCollision(MultiBoxesCollider* collider) const = 0;
        };
    }
}

#endif /* BOXCOLLIDER_H */

