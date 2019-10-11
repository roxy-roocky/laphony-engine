/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Engine.h
 * Author: nathan
 *
 * Created on September 6, 2019, 3:24 PM
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <list>

#include "../Frames/Updatable.h"
#include "Body.h"
#include "Raycast.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        class Body;
        class Collider;
        
        class Engine: public Frames::Updatable
        {
            public:
                Engine() = default;
                
                virtual void Update() override;
                
                void Register(Body* body);
                void Unregister(Body* body);
                
                std::list<Body*>& GetBodiesList();
                
                bool CheckIfIsValid(Collider* ptr) const;
                bool CheckIfIsValid(Body* ptr) const;
                
                Raycast* CreateRaycast(Point const& origin, Vector2d const& direction, int distance);
                
            private:
                std::list<Body*> _bodies;

        };
    }
}

#endif /* ENGINE_H */

