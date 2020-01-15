
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
        Collider::Collider(std::string const& tag, Rect const& rect, Body* parent): _tag(tag), _collider(rect), _parent(parent), _enabled(true)
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
                return  {_parent->Position().x + (_collider.x * std::abs(_parent->Scale().x)),
                         _parent->Position().y + (_collider.y * std::abs(_parent->Scale().y)),
                         _collider.w * std::abs(_parent->Scale().x),
                         _collider.h * std::abs(_parent->Scale().y)};
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
                
                Rect newCollider = thisTransCollider + Rect{thisColliderMove.x, thisColliderMove.y, 0, 0};
                
                if(newCollider.x + newCollider.w >= otherTranCollider.x && 
                   newCollider.x <= otherTranCollider.x + otherTranCollider.w &&
                   newCollider.y + newCollider.h >= otherTranCollider.y && 
                   newCollider.y <= otherTranCollider.y + otherTranCollider.h)
                {
                    if(thisColliderMove.x >= 0)
                    {
                        tmpDiff.x = otherTranCollider.x - thisTransCollider.x - thisTransCollider.w;
                    }

                    if(thisColliderMove.x <= 0)
                    {
                        double diff = otherTranCollider.x + otherTranCollider.w - thisTransCollider.x;
                        //if(tmpDiff.x == 0 || std::abs(diff) <= std::abs(tmpDiff.x))
                            tmpDiff.x += diff;                 
                    }

                    if(thisColliderMove.y >= 0)
                    {
                        tmpDiff.y = otherTranCollider.y - thisTransCollider.y - thisTransCollider.h;
                    }

                    if(thisColliderMove.y <= 0)
                    {
                        double diff = otherTranCollider.y + otherTranCollider.h - thisTransCollider.y;
                        //if(tmpDiff.y == 0 || std::abs(diff) <= std::abs(tmpDiff.y))
                            tmpDiff.y += diff;       
                    }
                }
                else
                    return false;
                
                if(diffenrence)
                    *diffenrence = tmpDiff;
                
                
                return true;
                    
            }
            
            return false;
        }
        
        Body* Collider::GetParentBody() 
        {
            return _parent;
        }
        
        void Collider::ChangeRect(Rect const& newRect)
        {
            _collider = newRect;
        }
        
        bool Collider::GetEnabled() const
        {
            return _enabled;
        }
        
        void Collider::SetEnabled(bool enable)
        {
            _enabled = enable;
        }
        
        Rect Collider::GetRect() const
        {
            return _collider;
        }

    }
}

