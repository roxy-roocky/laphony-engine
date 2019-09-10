/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StaticBody.h
 * Author: nathan
 *
 * Created on September 8, 2019, 10:07 PM
 */

#ifndef STATICBODY_H
#define STATICBODY_H

#include "Body.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        class Engine;
        
        class StaticBody: public virtual Body
        {
            public:
                virtual void PhysicUpdate(Engine* engine) override;
                
                
        };
    }
}


#endif /* STATICBODY_H */

