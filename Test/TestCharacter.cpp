/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCharacter.cpp
 * Author: nathan
 * 
 * Created on September 11, 2019, 8:13 PM
 */

#include <SDL2/SDL2_gfxPrimitives.h>

#include "TestCharacter.h"
#include "../Graphics/Animation.h"

TestCharacter::TestCharacter(Laphony::Graphics::Engine* gEngine): _onGround(false)
{
    Scale({1.5,1.5});
    
    SetCurrentAnimation("idLE");
    
    Position({300,400});
    
    Laphony::Graphics::Animator::Register("run", new Laphony::Graphics::Animation(new Laphony::Graphics::Image("Test/res/run-46-93.png",gEngine),{0,0,46,93}, 10, AUTOFREE, {23,93}), AUTOFREE);
    Laphony::Graphics::Animator::Register("idle", new Laphony::Graphics::Animation(new Laphony::Graphics::Image("Test/res/idle-52-82.png",gEngine),{0,0,52,82}, 14, AUTOFREE,  {26,82}), AUTOFREE);
        
        
    SetVelocity({0,1}); 
    
    _colliders.push_back(new Laphony::BasicPhysic::Collider("character", {0,0,52,82} , this));
    
}

bool TestCharacter::ManageCollision(const Collision& collision)
{
    if(collision.otherCollider && collision.otherCollider->GetParentBody()->GetIdentifierString() == "ground")
    {
        if(collision.diff.y < 0 && std::abs(collision.diff.x) > collision.diff.y*-1)
        {
            _onGround = true;
        }
    }
    
    return true;
}

std::string TestCharacter::GetIdentifierString() const
{
    return "character";
}


void TestCharacter::Display(Laphony::Graphics::Engine* engine)
{
    Laphony::Graphics::Animator::Display(engine);
    
    Laphony::Rect rect = (*_colliders.begin())->GetTransformedRect();
    
    rectangleRGBA(engine->Renderer(), rect.x, rect.y, rect.x+rect.w, rect.y+rect.h, 255, 0, 0, 255);
}

void TestCharacter::Update()
{
    Laphony::Graphics::Animator::Update();
    
    if(_colliders.size() > 0)
        delete *_colliders.begin();
    
    Laphony::Rect newRect = AnimationFromName(CurrentAnimationName())->GetCurrentRect();
    newRect.x = newRect.y = 0;
    
    _colliders.clear();
    _colliders.push_back(new Laphony::BasicPhysic::Collider("character", newRect, this));
    
    //gravity
   _velocity.y += 0.2;
   
   _onGround = false;
}

void TestCharacter::Jump()
{
    if(_onGround)
        _velocity.y = -5;
}

void TestCharacter::Move(double x)
{
    _velocity.x = x;
}

