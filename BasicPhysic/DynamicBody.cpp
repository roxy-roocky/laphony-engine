/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DynamicBody.cpp
 * Author: nathan
 * 
 * Created on September 8, 2019, 10:25 PM
 */

#include "DynamicBody.h"
#include "Engine.h"
#include "Collider.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        void DynamicBody::PhysicUpdate(Engine* engine)
        {
            if(!engine)
                return;
            
            _position.x += _velocity.x;
            _position.y += _velocity.y;
            
            _currentCollisions.clear();
            
            for(Body* body : engine->GetBodies())
                if(body)
                {
                    for(Collider* collider : body->GetColliders())
                        if(collider)
                        {
                            for(Collider* myCollider : _colliders)
                                if(myCollider)
                                {
                                    if(collider->CheckCollision(myCollider))
                                        _currentCollisions.push_back(collider);
                                }
                        }
                    
                }
            
            if(_currentCollisions.size() > 0)
            {
                _position.x -= _velocity.x;
                _position.y -= _velocity.y;
                
                _velocity = _velocity * 0.5;
            }
            
        }
        
        Vector2d DynamicBody::GetVelocity() const
        {
            return _velocity;
        }
        
        void DynamicBody::SetVelocity(const Vector2d& velocity)
        {
            _velocity = velocity;
        }
    }
}

