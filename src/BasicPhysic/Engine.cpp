/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Engine.cpp
 * Author: nathan
 * 
 * Created on September 6, 2019, 3:24 PM
 */

#include "Engine.h"

#include "Body.h"

namespace Laphony
{
    namespace BasicPhysic
    {

        Engine::Engine() 
        {

        }

        
        void Engine::Update()
        {
            for(Body* body : _bodies)
                if(body)
                    body->GetCollisionsList().clear();
            
            for(Body* body : _bodies)
                if(body)
                    body->PhysicUpdate(this);
        }
        
        void Engine::Register(Body* body)
        {
            _bodies.push_back(body);
        }
        
        void Engine::Unregister(Body* body)
        {
            _bodies.remove(body);
        }
        
        std::list<Body*>& Engine::GetBodiesList()
        {
            return _bodies;
        }
        
        bool Engine::CheckIfIsValid(Body* ptr) const 
        {
            for(Body* body: _bodies)
                if(body == ptr)
                    return true;
            
            return false;
        }
        
        bool Engine::CheckIfIsValid(Collider* ptr) const
        {
            for(Body* body: _bodies)
                if(body)
                {
                    for(Collider* collider: body->GetCollidersList())
                        if(collider == ptr)
                        {
                            return true;
                        }
                }
                    
            return false;
        }
        
        Raycast* Engine::CreateRaycast(const Point& origin, const Vector2d& direction, int distance)
        {
            return new Raycast(origin, direction, distance, this);
        }

    }
}