/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestMovingSquare.h
 * Author: nathan
 *
 * Created on February 3, 2020, 2:22 PM
 */

#ifndef TESTMOVINGSQUARE_H
#define TESTMOVINGSQUARE_H

#include "../BasicPhysic/DynamicBody.h"
#include "../Graphics/Displayable.h"
#include "../Graphics/Engine.h"

class TestMovingSquare: public Laphony::BasicPhysic::DynamicBody, public Laphony::Graphics::Displayable
{
    public:
        TestMovingSquare();
        
        virtual std::string GetIdentifierString() const;
                
        virtual bool ManageCollision(Collision const& collision) override;
        virtual void Display(Laphony::Graphics::Engine* engine) override;
        virtual void NoCollision() override {}
        
        
};

#endif /* TESTMOVINGSQUARE_H */

