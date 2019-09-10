/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Body.cpp
 * Author: nathan
 * 
 * Created on September 6, 2019, 5:26 PM
 */

#include "Body.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        std::list<Collider*>& Body::GetColliders()
        {
            return _colliders;
        }
    }
}

