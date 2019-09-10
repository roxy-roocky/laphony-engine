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
        void Engine::Update()
        {
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
        
        std::list<Body*>& Engine::GetBodies()
        {
            return _bodies;
        }
    }
}