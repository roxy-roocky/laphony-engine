/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Slope.cpp
 * Author: nathan
 * 
 * Created on September 17, 2019, 5:20 PM
 */

#include <list>

#include "Slope.h"

Slope::Slope(Laphony::Graphics::Engine* gEngine, int w, int h, bool leftToRight): _leftToRight(leftToRight)
{
    double ratio = static_cast<double>(h)/static_cast<double>(w);
    if(leftToRight)
        for(int i=0; i<w; i++)
        {
            double currentH = i*ratio + 1;
            _colliders.push_back(new Laphony::BasicPhysic::Collider("slope", {i,h-currentH,w-i,currentH}, this));
        }
    else
        for(int i=0; i<w; i++)
        {
            double currentH = h - i*ratio + 1;
            _colliders.push_back(new Laphony::BasicPhysic::Collider("slope", {i,h-currentH,w-i, currentH}, this));
        }
}

std::string Slope::GetIdentifierString() const
{
    if(_leftToRight)
        return "slopelr";
    else
        return "sloperl";
}

void Slope::Display(Laphony::Graphics::Engine* engine)
{
    //Laphony::Graphics::Image::Display(engine);
    
    for(Laphony::BasicPhysic::Collider* c : _colliders)
    {
        Laphony::Rect rect = c->GetTransformedRect();
    
        rectangleRGBA(engine->Renderer(), rect.x, rect.y, rect.x+rect.w, rect.y+rect.h, 255, 0, 0, 255);
    }
}

