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

#include "Engine.h"
#include "Collider.h"

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
        
        std::vector<std::string>& Raycast::GetIgnoredCollidersTags()
        {
            return _ignoredCollidersTags;
        }
        
        bool Raycast::Proceed(int maxHitsCount)
        {
            if(!_engine)
                return false;
            

            
            double a;
            
            if(_direction.x == 0)
                a = 0;
            else
                a = _direction.y/_direction.x;
            
            double b = _origin.y;
            
            //  y = ax+b;
            
            _hitsColliders.clear();
            Point pt = _origin;
            double currentDistance = 0.0;
            int hits = 0;
            
            do
            {
                if(a != 0)
                    pt.y = a*pt.x + b;
                
                for(Body* body : _engine->GetBodiesList())
                    if(body)
                    {
                        for(Collider* collider : body->GetCollidersList())
                            if(collider)
                            { 
                                bool no = false;
                                if(PointInRect(pt, collider->GetTransformedRect()))
                                {
                                    for(std::string tag: _ignoredCollidersTags)
                                    {
                                        std::string ctag = collider->GetTag();
                                        if(ctag == tag)
                                        {
                                            no = true;
                                            break;
                                        }
                                    
                                    }
                                        
                                    if(!no)
                                    {
                                        _hitsColliders.push_back(collider);
                                            hits++;
                                    }
                                }
                                
                                
                                
                            }
                    }
                if(a != 0)
                    pt.x += 1;
                else
                    pt.y += _direction.y/std::abs(_direction.y);
                
                currentDistance = std::sqrt(std::pow(_origin.x - pt.x, 2) + std::pow(_origin.y - pt.y, 2));
                
            }while((maxHitsCount < 0 || hits < maxHitsCount) && currentDistance <= _distance);
            
            return hits > 0;
        }
        
        Point Raycast::GetOrigine() const
        {
            return _origin;
        }
        
        void Raycast::SetOrigin(const Point& newOrigin)
        {
            _origin = newOrigin;
        }

    }
}


