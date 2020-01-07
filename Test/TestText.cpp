/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestText.cpp
 * Author: nathan
 * 
 * Created on May 23, 2019, 9:09 PM
 */

#include "TestText.h"
#include "TestRectangle.h"

TestText::TestText(std::string const& str) : BasicFontText("Test/Cabin-Regular.ttf",str,{400,300}, 20, false, {255,255,255,255}, {0,0,0,0}), _direction(0)
{ 
    
}

void TestText::Update()
{
    if(_direction)
    {
        Scale({Scale().x + 0.01, Scale().y +0.01});
        if(Scale().x > 2)
            _direction = 0;
    }
    else
    {
        Scale({Scale().x - 0.01, Scale().y - 0.01});
        if(Scale().x < 0.2)
            _direction = 1;
    }
   
    
    //_pivot.x = (_text.size()*FONT_SIZE*_scale.x) / 2;
    //_pivot.y =(FONT_SIZE*_scale.y)/2;
}




