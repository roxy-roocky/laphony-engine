/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCharacter.h
 * Author: nathan
 *
 * Created on September 11, 2019, 8:13 PM
 */

#ifndef TESTCHARACTER_H
#define TESTCHARACTER_H

#include "../Transformable.h"
#include "../Graphics/Animator.h"
#include "../Graphics/Displayable.h"

#include "../BasicPhysic/DynamicBody.h"
#include "../BasicPhysic/Raycast.h"

#include "../Sound/Speaker.h"
#include "../Sound/Engine.h"

class TestCharacter: public virtual Laphony::Transformable, public virtual Laphony::BasicPhysic::DynamicBody, public virtual Laphony::Graphics::Animator, public virtual Laphony::Sound::Speaker
{
    public:
        TestCharacter(Laphony::Graphics::Engine* gEngine, Laphony::BasicPhysic::Engine* pEngine, Laphony::Sound::Engine* sndEngine);        

        virtual std::string GetIdentifierString() const;
                
        virtual bool ManageCollision(Collision const& collision) override;
        virtual void NoCollision() override;

        
        virtual void Display(Laphony::Graphics::Engine* engine) override;
        virtual void Update() override;

        void Jump();
        void Move(bool right);
        
    private:
        bool _onGround;
        
        Laphony::Graphics::Animation* _currentAnimation;
        
        Laphony::BasicPhysic::Raycast *_rcGroundL, *_rcGroundC, *_rcGroundR;       
        
};

#endif /* TESTCHARACTER_H */

