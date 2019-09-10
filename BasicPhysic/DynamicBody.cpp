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
            
            //For each bodies in engine
            for(Body* body : engine->GetBodiesList())
                if(body)
                {
                    //for each of his colliders
                    for(Collider* collider : body->GetCollidersList())
                        if(collider)
                        {
                            //for each of this body colliders
                            for(Collider* thisCollider : this->GetCollidersList())
                                if(thisCollider)
                                {
                                    Body::Collision collision;
                                    
                                    //if there is collision
                                    if(thisCollider->CheckIfCollision(collider, _velocity, &collision.diff))
                                    {
                                        //Add collision
                                        collision.otherCollider = collider;
                                        _currentCollisions.push_back(collision);
                                    }
                                }
                        }
                }
            
            //Manage collisions
            for(Collision& collision: _currentCollisions)
            {
                if(CheckIfManageCollision(collision))
                {
                    //Move the body
                    _position.x -= collision.diff.x;
                    _position.y -= collision.diff.y;
                    
                }
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

