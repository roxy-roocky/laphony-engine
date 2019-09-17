/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGround.h
 * Author: nathan
 *
 * Created on September 10, 2019, 10:40 AM
 */

#ifndef TESTGROUND_H
#define TESTGROUND_H

#include "../Structs.h"
#include "../Transformable.h"

#include "../BasicPhysic/StaticBody.h"
#include "../Graphics/Image.h"
#include "TestRectangle.h"

class TestGround: public virtual Laphony::Transformable, public virtual Laphony::BasicPhysic::StaticBody, public virtual Laphony::Graphics::Image
{
    public:
        TestGround(Laphony::Graphics::Engine* gEngine, int w = 800, int h = 600);
        virtual std::string GetIdentifierString() const override;
        virtual void Display(Laphony::Graphics::Engine* engine) override;
};

#endif /* TESTGROUND_H */
