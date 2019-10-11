/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/**
 * \file   Structs.h
 * \brief Commons structures
 * \author Nathan Baumann
 * \date march 21 2019, 07:04 am
 */

/**\mainpage Laphony Engine
 * 
 *  This engine is a game engine compose of severals sub-engines. It is write in C++ and use the SDL 2 library. \n
 *  It is not the definitive version so come sometime look for new updates ;) \n
 *  \n
 *  Kiss, Nathan
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL2/SDL.h>

#define AUTOFREE true

namespace Laphony
{
    /**
     * \struct Laphony::Rect
     * \brief Represents a (x, y, w, h) rectangle
     * 
     * Actually is a typedef of SDL_Rect.
     */
    struct Rect
    {
        double x, y, w, h;
    };
    
    Rect operator+(Rect const& r1, Rect const& r2);
    
    Rect operator-(Rect const& r1, Rect const& r2);
    
    Rect operator*(Rect const& r, double d);
    
    /**
     * \struct Laphony::Point
     * \brief Represents a (x, y) point
     * 
     * 
     * Actually is a typedef of SDL_Point.
     */
    struct Point
    {
        double x, y;
    };
    
    Point operator+(Point const& p1, Point const& p2);
    
    Point operator-(Point const& p1, Point const& p2);
    
    Point operator*(Point const& p, double d);
    
    /**
     * \brief Represents a vector of 2 elements
     */
    struct Vector2d
    {
        double x, y;
        
    };
    
    Vector2d operator+(Vector2d const& p1, Vector2d const& p2);
    
    Vector2d operator-(Vector2d const& p1, Vector2d const& p2);
    
    Vector2d operator*(Vector2d const& p, double d);
    
    bool PointInRect(Point const& point, Rect const& rect);
}

#endif /* STRUCTS_H */

