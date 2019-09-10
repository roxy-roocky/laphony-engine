
/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   BasicPhysic/Collider.cpp
 * \author Nathan Baumann
 *
 * \date august 29 2019, 5:19 PM
 */

#include <vector>

#include "Collider.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        Collider::Collider(std::string const& tag, Rect const& rect, Body* parent): _tag(tag), _collider(rect), parent(parent)
        {
        }
        
        std::string Collider::GetTag() const 
        {
            return _tag;
        }
        
        void Collider::SetTag(std::string const& tag)
        {
            _tag = tag;
        }
        
        Rect Collider::GetTransformedRect() const
        {
            if(_parent)
                return  {_collider.x + _parent->Position().x,
                         _collider.y + _parent->Position().y,
                         _collider.w * _parent->Scale().x,
                         _collider.h * _parent->Scale().y};
            else
                return _collider;
        }
        
        bool Collider::CheckIfCollision(Collider* collider, Vector2d const& thisColliderMove, Vector2d* diffenrence)
        {
            if(collider)
            {
                Vector2d tmpDiff = {0,0};
                Rect thisTransCollider = GetTransformedRect();
                Rect otherTranCollider = collider->GetTransformedRect();
                
                //Check on X
                bool canHaveCollisionOnX = false;
                if(thisColliderMove.x > 0 || thisColliderMove.x == 0)
                {
                    tmpDiff.x = thisTransCollider.x + thisTransCollider.w + thisColliderMove.x - otherTranCollider.x;
                    canHaveCollisionOnX = tmpDiff.x > 0;
                }
                
                if(thisColliderMove.x < 0 || thisColliderMove.x == 0)
                {
                    tmpDiff.x = thisTransCollider.x + thisColliderMove.x - otherTranCollider.x + otherTranCollider.w;
                    canHaveCollisionOnX = tmpDiff.x < 0;
                }
                
                //Check on Y
                bool canHaveCollisionOnY = false;
                if(thisColliderMove.y > 0 || thisColliderMove.y == 0)
                {
                    tmpDiff.y = thisTransCollider.y + thisTransCollider.h + thisColliderMove.y + otherTranCollider.y;
                    canHaveCollisionOnY = tmpDiff.y > 0;
                }
                
                if(thisColliderMove.y < 0 || thisColliderMove.y == 0)
                {
                    tmpDiff.y = thisTransCollider.y + thisColliderMove.y - otherTranCollider.y + otherTranCollider.h;
                    canHaveCollisionOnY = tmpDiff.y < 0;
                }
                
                if(diffenrence)
                    (*diffenrence) = tmpDiff;
                
                return canHaveCollisionOnX && canHaveCollisionOnY;
            }
            
            return false;
        }
    }
}

