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
#include <cmath>
#include <vector>
#include "../Transformable.h"
#include "Engine.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        class Body;
        
        class Collider
        {                
            public:
                Collider(std::string const& tag, Rect const& rect, Body* parent);
                
                std::string GetTag() const;
                void SetTag(std::string const& tag);
                
                Body* GetParentBody();
                
                bool CheckIfCollision(Collider* collider, Vector2d const& thisColliderMove, Vector2d* diffenrence = nullptr);
                Rect GetTransformedRect() const;
                Rect GetRect() const;
                
                bool GetEnabled() const;
                void SetEnabled(bool enable);
                
                void ChangeRect(Rect const& newRect);
            private:
                std::string _tag;
                Rect _collider;
                
                Body* _parent;
                
                bool _enabled;
                
                std::vector<Collider*> _collisions;
                
        };
    }
}

#endif /* COLLIDER_H */

