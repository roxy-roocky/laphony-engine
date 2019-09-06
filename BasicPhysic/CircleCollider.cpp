/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CircleCollider.cpp
 * Author: nathan
 * 
 * Created on September 2, 2019, 10:52 PM
 */

#include "CircleCollider.h"
#include "BoxCollider.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        CircleCollider::CircleCollider(std::string const& tag): Collider(tag)
        {
            
        }
        
        Point CircleCollider::ComputeRealCenter() const
        {
            Point realCenter = _center;
            realCenter.x += _position.x;
            realCenter.y += _position.y;
            
            return realCenter;
        }
        
        int CircleCollider::ComputeRealRadius() const
        {
            double averrageScale = std::abs(_scale.x) + std::abs(_scale.y) / 2.0;
            
            return _radius * averrageScale;
        } 
        
        
        bool CircleCollider::CollisionWith(Collider* collider)
        {
            return CheckCollision(this);
        }
        
        bool CircleCollider::CheckCollision(BoxCollider* collider)
        {
            return collider->CollisionWith(this);
        }
        
        bool CircleCollider::CheckCollision(CircleCollider* collider)
        {
            if(!collider)
                return false;
            
            Point realCenter = ComputeRealCenter();
            Point realOtherCenter = collider->ComputeRealCenter();
            
            int distance = std::sqrt(std::pow(realCenter.x - realOtherCenter.x, 2) + std::pow(realCenter.y - realOtherCenter.y, 2));
            
            return distance <= ComputeRealRadius() + collider->ComputeRealRadius();
        }
        
     
    }
}



