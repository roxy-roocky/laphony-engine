/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DynamicBody.h
 * Author: nathan
 *
 * Created on September 8, 2019, 10:25 PM
 */

#ifndef DYNAMICBODY_H
#define DYNAMICBODY_H

#include "../Structs.h"

#include "Body.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        class Engine;
        
        class DynamicBody: public virtual Body
        {
            public:
                virtual void PhysicUpdate(Engine* engine) override;
               
                virtual std::string GetIdentifierString() const = 0;
                
                virtual bool ManageCollision(Collision const& collision) = 0;
                virtual void NoCollision() = 0;
                
                Vector2d GetVelocity() const;
                void SetVelocity(Vector2d const& velocity);
                
            protected:
                Vector2d _velocity;

        };
    }
}

#endif /* DYNAMICBODY_H */

