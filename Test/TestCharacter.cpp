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

#include <iostream>

TestCharacter::TestCharacter(Laphony::Graphics::Engine* gEngine, Laphony::BasicPhysic::Engine* pEngine, Laphony::Sound::Engine* sndEngine):Speaker(sndEngine), _onGround(false), _rcGroundL(nullptr), _rcGroundC(nullptr), _rcGroundR(nullptr)
{
    SetMaxAudibleDistance(800);
    StickOnListener(false);
    Scale({1.2,1.2});
    
    SetCurrentAnimation("idLE");
    
    Position({300,400});
    
    Laphony::Graphics::Animator::Register("run", new Laphony::Graphics::Animation(new Laphony::Graphics::Image("Test/res/run-46-93.png",gEngine),{0,0,46,93}, 10, AUTOFREE, {23,93}), AUTOFREE);
    Laphony::Graphics::Animator::Register("idle", new Laphony::Graphics::Animation(new Laphony::Graphics::Image("Test/res/idle-52-82.png",gEngine),{0,0,52,82}, 14, AUTOFREE,  {26,82}), AUTOFREE);
//        
        
    //SetVelocity({0,1}); 
    
    _colliders.push_back(new Laphony::BasicPhysic::Collider("character", {-26, -82, 52, 82} , this));
    
    SetCurrentAnimation("idle");
    _currentAnimation = AnimationFromName(CurrentAnimationName());
    
    _rcGroundC = pEngine->CreateRaycast(Position(), {0,1}, 1);
    _rcGroundC->GetIgnoredCollidersTags().push_back("player");
    
    _rcGroundL = pEngine->CreateRaycast(Position(), {0,1}, 1);
    _rcGroundL->GetIgnoredCollidersTags().push_back("player");
    
    _rcGroundR = pEngine->CreateRaycast(Position(), {0,1}, 1);
    _rcGroundR->GetIgnoredCollidersTags().push_back("player");
}

bool TestCharacter::ManageCollision(const Collision& collision)
{
    if(collision.otherCollider)
    {
       
        if(_velocity.x != 0)
        {
            if(collision.otherCollider->GetParentBody()->GetIdentifierString() == "slopelr")
            {
                _velocity.y += 0.005;
               
            }

            if(collision.otherCollider->GetParentBody()->GetIdentifierString() == "sloperl" )
            {
                _velocity.y -= 0.005;
               
            }
        }
    }
    
    return true;
}

void TestCharacter::NoCollision() 
{
   
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
    
    Laphony::Graphics::Animation* newAnimation = AnimationFromName(CurrentAnimationName());
    
    Laphony::Rect rect = (*_colliders.begin())->GetTransformedRect();
    
    _rcGroundC->SetOrigin(Position());
    _rcGroundL->SetOrigin({Position().x - rect.w/2 + 2, Position().y});
    _rcGroundR->SetOrigin({Position().x + rect.w/2 - 2, Position().y});
    _onGround = _rcGroundL->Proceed(1) || _rcGroundC->Proceed(1) || _rcGroundR->Proceed(1);

    /*if(newAnimation != _currentAnimation)
    {
        if(*_colliders.begin())
        {
            Laphony::Rect newRect = newAnimation->GetCurrentRect();
            newRect.x = -newRect.w/2;
            newRect.y = -newRect.h;
            (*_colliders.begin())->ChangeRect(newRect);
            
            _currentAnimation = newAnimation;
        }
    }*/
    
    //gravity
    _velocity.y += 1;

    double friction = 0 -(_velocity.x/std::abs(_velocity.x))*(_onGround?1:1);

    if((_velocity.x + friction) * _velocity.x > 0)
    {
        _velocity.x += friction;
    }
    else
        _velocity.x = 0;
    
    
 
}

void TestCharacter::Jump()
{
    
    if(_onGround)
    {
        Play("jump");
        _velocity.y = -15;
    }
}

void TestCharacter::Move(bool right)
{
    _velocity.x = (right?-1:1)*4;
}

