/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   BasicPhysic/MultiBoxesCollider.h
 * \author Nathan Baumann
 *
 * \date  September 2, 2019, 10:12 PM
 */

#ifndef MULTIBOXESCOLLIDER_H
#define MULTIBOXESCOLLIDER_H

#include <list>
#include "Collider.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        class MultiBoxesCollider: public virtual Collider
        {
            public:
                MultiBoxesCollider(std::string const& tag);

                virtual Type GetType() const {return Type::MULTIPLEBOXES;}
            
            private:
                virtual bool CheckCollision(BoxCollider* collider) const = 0;
                virtual bool CheckCollision(CircleCollider* collider) const = 0;
                virtual bool CheckCollision(MultiBoxesCollider* collider) const = 0;
                
                
                std::list<Rect> _boxes;
        };
    }
}

#endif /* MULTIBOXESCOLLIDER_H */

