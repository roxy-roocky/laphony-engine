/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Body.h
 * Author: nathan
 *
 * Created on September 6, 2019, 5:26 PM
 */

#ifndef BODY_H
#define BODY_H

#include <vector>
#include <list>
#include "../Transformable.h"
#include "Collider.h"


namespace Laphony
{
    namespace BasicPhysic
    {
        class Collider;
        class Engine;
        
        class Body: public virtual Transformable
        {
            public:
                Body();
                
                virtual void PhysicUpdate(Engine* engine) = 0;
                
                std::list<Collider*>& GetColliders();                
            
            protected:

                std::list<Collider*> _colliders;

                std::vector<Collider*> _currentCollisions;
        };
    }
}

#endif /* BODY_H */

