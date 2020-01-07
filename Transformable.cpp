/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   Transformable.cpp
 * Author: Nathan Baumann
 *
 * Created on 17 avril 2019, 22:36
 */

#include <cmath>

#include "Transformable.h"

namespace Laphony
{
    Transformable::Transformable(): Transformable({0,0}, 0, {1,1})
    {
        
    }
    
     Transformable::Transformable(Point const& position, double angle, Vector2d const& scale): _position(position), _angle(angle), _scale(scale)
     {
         
     }
    
    Point Transformable::Position() const {return _position;}
    
    
        
    double Transformable::Angle() const {return _angle;}

    Vector2d Transformable::Scale() const {return _scale;}
    
    void Transformable::Translate(Vector2d const& v) 
    {
        Position({Position().x + v.x, Position().y + v.y});
    }


    void Transformable::Position(Point const& point)
    {
        _position = point;
    }
    
    
    void Transformable::Angle(double const& angle)
    {
        _angle = angle;
    }
    
    void Transformable::Rotate(double const& v)
    {
        _angle += v;
    }

    void Transformable::Scale(Vector2d const& scale)
    {
        _scale = scale;
    }
    
    Transformable& Transformable::operator+=(Transformable const& t)
    {
        Position(_position + t._position);
        _angle += t._angle;
        
        _scale.x *= t._scale.x;
        _scale.y *= t._scale.y;
        
    }
   
}
