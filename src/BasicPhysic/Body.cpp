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
        Body::~Body(){
            for (auto c : _colliders) {
                delete c;
            }

        }
        
        Body::Collision::Collision(): collider(nullptr), otherCollider(nullptr), diff{0,0}
        {

        }

        std::list<Collider*>& Body::GetCollidersList()
        {
            return _colliders;
        }
        
        std::vector<Body::Collision>& Body::GetCollisionsList()
        {
            return _currentCollisions;
        }
        
        void Body::SetEnabledCollidersWithTag(const std::string& tag, bool enable)
        {
            for(Collider* c : _colliders)
                if(c && c->GetTag() == tag)
                {
                    c->SetEnabled(enable);
                }
        }
        
    }
}

