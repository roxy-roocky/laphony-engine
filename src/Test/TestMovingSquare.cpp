/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestMovingSquare.cpp
 * Author: nathan
 * 
 * Created on February 3, 2020, 2:23 PM
 */

#include "TestMovingSquare.h"
#include <SDL2/SDL2_gfxPrimitives.h>

TestMovingSquare::TestMovingSquare()
{
    _colliders.push_back(new Laphony::BasicPhysic::Collider("moving", {0,0,30,30} , this));
}

std::string TestMovingSquare::GetIdentifierString() const
{
    return "moving";
}

void TestMovingSquare::Display(Laphony::Graphics::Engine* engine)
{
    //Laphony::Graphics::Image::Display(engine);
    
    Laphony::Rect rect = (*_colliders.begin())->GetTransformedRect();
    
    rectangleRGBA(engine->Renderer(), rect.x, rect.y, rect.x+rect.w, rect.y+rect.h, 255, 255, 0, 255);
}

bool TestMovingSquare::ManageCollision(Collision const& collision)
{
    return true;
}

