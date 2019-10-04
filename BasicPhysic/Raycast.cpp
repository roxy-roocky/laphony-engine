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
            if(!_engine)
                return false;
            
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
            Point pt = {0,0};
            double currentDistance = 0.0;
            int hits = 0;
            
            do
            {
                pt.y = std::round(-(a/b)*pt.x -(b/c));
                
                for(Body* b : _engine->GetBodiesList())
                    if(b)
                    {
                        for(Collider* c : b->GetCollidersList())
                            if(c)
                            {
                                if(PointInRect(pt, c->GetTransformedRect()))
                                {
                                    _hitsColliders.push_back(c);
                                    hits++;
                                }
                            }
                    }
                currentDistance = std::sqrt(std::pow(_origin.x - pt.x, 2) + std::pow(_origin.y - pt.y, 2));
                
            }while((maxHitsCount < 0 || hits < maxHitsCount) && currentDistance <= _distance);
            
            return hits > 0;
        }

    }
}


