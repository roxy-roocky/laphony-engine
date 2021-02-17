/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Slope.h
 * Author: nathan
 *
 * Created on September 17, 2019, 5:20 PM
 */

#ifndef SLOPE_H
#define SLOPE_H

#include "../Structs.h"
#include "../Transformable.h"
#include "../BasicPhysic/StaticBody.h"
#include "../Graphics/Displayable.h"

#include "../Graphics/Engine.h"

class Slope: public virtual Laphony::Transformable, public virtual Laphony::BasicPhysic::StaticBody, public virtual Laphony::Graphics::Displayable
{
    public:
        Slope(Laphony::Graphics::Engine* gEngine, int w, int h, bool leftToRight = true);
        
        virtual std::string GetIdentifierString() const override;
        virtual void Display(Laphony::Graphics::Engine* engine) override;
        
    private:
        bool _leftToRight;
};

#endif /* SLOPE_H */

