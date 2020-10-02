/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Structs.h"
#include <cmath>
#include <ostream>

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
        return Rect{r.x * d, r.y * d, r.w * d, r.h * d};
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
        return Vector2d{p.x * d, p.y * d};
    }
    
    bool PointInRect(Point const& point, Rect const& rect)
    {
        return point.x >= rect.x && point.x <= rect.x + rect.w && point.y > rect.y && point.y < rect.y + rect.h;
    }
    
    std::ostream& operator <<(std::ostream& out, const Vector2d& v)
    {
        out << "(" << v.x << ";" << v.y << ")";;
        
        return out;
    }
}
