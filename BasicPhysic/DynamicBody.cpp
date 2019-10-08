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

#include <iostream>

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
            
            //For each bodies in engine
            for(Body* body : engine->GetBodiesList())
                if(body && body != this)
                {
                    //for each of his colliders
                    for(Collider* collider : body->GetCollidersList())
                        if(collider && collider->GetEnabled())
                        {
                            //for each of this body colliders
                            for(Collider* thisCollider : this->GetCollidersList())
                                if(thisCollider && collider->GetEnabled())
                                {
                                    Body::Collision collision;
                                    
                                    //if there is collision
                                    if(thisCollider->CheckIfCollision(collider, _velocity, &collision.diff))
                                    {
                                        //Add collision
                                        collision.otherCollider = collider;
                                        collision.collider = thisCollider;
                                        _currentCollisions.push_back(collision);
                                        
                                        
                                    }
                                }
                        }
                    
                }
            

            Point move = {0,0};
            //Manage collisions
            for(Collision& collision: _currentCollisions)
            {
                if(ManageCollision(collision))
                {

                    if(std::abs(collision.diff.x) < std::abs(collision.diff.y) && _velocity.x * collision.diff.x < 0)//if velocity and diff in opposite signed
                    {
                        
                        
                            if(std::abs(collision.diff.x) > std::abs(move.x))
                                 move.x = collision.diff.x ;
              
                           
                        
                    }
                    
                    if(std::abs(collision.diff.y) < std::abs(collision.diff.x) && _velocity.y * collision.diff.y < 0)//if velocity and diff in opposite signed
                    {
                        
                        
                            if(std::abs(collision.diff.y) > std::abs(move.y))
                                 move.y = collision.diff.y ;
                       
                    }
                        
                }
            }
            
            //std::cout << "Move: " << move.x << ";"<< move.y << std::endl;
            _position = _position + move;
            
            if(move.x != 0)
                _velocity.x = 0;
            if(move.y != 0)
                _velocity.y = 0;
            
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

