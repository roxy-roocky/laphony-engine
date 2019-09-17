/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGround.cpp
 * Author: nathan
 * 
 * Created on September 10, 2019, 10:40 AM
 */

#include "TestGround.h"

TestGround::TestGround(Laphony::Graphics::Engine* gEngine,int w, int h): Image(w, h, {255,255,255}, gEngine)
{
    _colliders.push_back(new Laphony::BasicPhysic::Collider("ground", {0,0,w,h} , this));
}


std::string TestGround::GetIdentifierString() const
{
    return "ground";
}

void TestGround::Display(Laphony::Graphics::Engine* engine)
{
    //Laphony::Graphics::Image::Display(engine);
    
    Laphony::Rect rect = (*_colliders.begin())->GetTransformedRect();
    
    rectangleRGBA(engine->Renderer(), rect.x, rect.y, rect.x+rect.w, rect.y+rect.h, 255, 0, 0, 255);
}
