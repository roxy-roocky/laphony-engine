/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Raycast.cpp
 * Author: nathan
 * 
 * Created on September 21, 2019, 1:08 PM
 */

#include "Raycast.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        Raycast::Raycast(const Point& origin, const Vector2d& direction, int distance, Engine* engine): _origin(origin), _direction(direction), _distance(std::abs(distance)), _engine(engine)
        {
            
        }
        
        std::vector<Collider*>& Raycast::GetHitsCollidersList()
        {
            return _hitsColliders;
        }
        
        bool Raycast::Proceed(int maxHitsCount)
        {
            double a = _direction.y;
            double b = -_direction.x;
            double c = -a*_origin.x -b*_origin.y;
            
            //  ax + by + c   = 0
            //  ax + by       = -c
            //  by            = -c -ax
            //  y             = (-c -ax)/b 
            //                = (c + ax) / -b
            //                = -(a/b)x -(b/c)
            
            _hitsColliders.clear();
            
            
        }

    }
}


