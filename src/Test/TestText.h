/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestText.h
 * Author: nathan
 *
 * Created on May 23, 2019, 9:09 PM
 */

#ifndef TESTTEXT_H
#define TESTTEXT_H

#include "../Graphics/Engine.h"
#include "../Graphics/BasicFontText.h"
#include "../Frames/Updatable.h"

class TestText: public Laphony::Graphics::BasicFontText, public Laphony::Frames::Updatable
{
    public: 
        TestText(std::string const& str);

        void Update() override;

        
    private :
        int _direction;

};

#endif /* TESTTEXT_H */

