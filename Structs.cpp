/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Structs.h"
#include <cmath>

namespace Laphony
{
    Rect operator+(Rect const& r1, Rect const& r2)
    {
        return Rect{r1.x + r2.x, r1.y + r2.y, r1.w + r2.w, r1.h + r2.h};
    }
    
    Rect operator-(Rect const& r1, Rect const& r2)
    {
        return Rect{r1.x - r2.x, r1.y - r2.y, r1.w - r2.w, r1.h - r2.h};
    }
    
    Rect operator*(Rect const& r, double d)
    {
        return Rect{std::round(r.x * d), std::round(r.y * d), std::round(r.w * d), std::round(r.h * d)};
    }
    
    
    
    Point operator+(Point const& p1, Point const& p2)
    {
        return Point{p1.x + p2.x, p1.y + p2.y};
    }
    
    Point operator-(Point const& p1, Point const& p2)
    {
        return Point{p1.x - p2.x, p1.y - p2.y};
    }
    
    Point operator*(Point const& p, double d)
    {
        return Point{std::round(p.x * d), std::round(p.y * d)};
    }
    
    
    Vector2d operator+(Vector2d const& p1, Vector2d const& p2)
    {
        return Vector2d{p1.x + p2.x, p1.y + p2.y};
    }
    
    Vector2d operator-(Vector2d const& p1, Vector2d const& p2)
    {
        return Vector2d{p1.x - p2.x, p1.y - p2.y};
    }
    
    Vector2d operator*(Vector2d const& p, double d)
    {
        return Vector2d{std::round(p.x * d), std::round(p.y * d)};
    }
    
    bool PointInRect(Point const& point, Rect const& rect)
    {
        return point.x >= rect.x && point.x <= rect.x + rect.w && point.y > rect.y && point.y < rect.y + rect.h;
    }
}
