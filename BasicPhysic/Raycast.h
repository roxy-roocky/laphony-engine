/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Raycast.h
 * Author: nathan
 *
 * Created on September 21, 2019, 1:08 PM
 */

#ifndef RAYCAST_H
#define RAYCAST_H

#include "Collider.h"

#include <vector>


namespace Laphony
{
    namespace BasicPhysic
    {
        class Raycast
        {
            friend class Laphony::BasicPhysic::Engine;
            
            public:
                bool Proceed(int maxHitsCount = -1);
                std::vector<Collider*>& GetHitsCollidersList();
                
            private:
                Raycast(Point const& origin, Vector2d const& direction, int distance, Engine* engine);
                
                Point _origin;
                Vector2d _direction;
                int _distance;
                
                std::vector<Collider*> _hitsColliders;
                
                Engine* _engine;

        };
    }
}

#endif /* RAYCAST_H */

