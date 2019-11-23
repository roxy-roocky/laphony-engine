/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * File:   main.cpp
 * Author: Nathan Baumann
 *
 * Created on 20 mars 2019, 21:18
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <unistd.h>
#include "Graphics/Engine.h"
#include "Graphics/Surface.h"
#include "Graphics/Image.h"

#include "Frames/Engine.h"

#include "Test/TestRectangle.h"

#include "Graphics/BasicText.h"

#include "Events/Engine.h"
#include "Test/TestText.h"
#include "Graphics/Animation.h"
#include "Graphics/Animator.h"

#include "BasicPhysic/Engine.h"
#include "Test/TestGround.h"
#include "Test/TestCharacter.h"
#include "Test/Slope.h"
#include "Events/MouseButtonControl.h"
#include "Frames/ThreadEngine.h"
#include "Test/TestCounterThread.h"
/*
 * 
 */
int main(int argc, char** argv) 
{
    //freopen("CONOUT$","wt",stdout);
    
    srand(time(nullptr));
    
#ifdef DEBUG
    #ifndef WINDOWS
        setenv("LIBGL_DEBUG","verbose",1);
    #endif
#endif
    
    Laphony::Frames::Engine fEngine(50);
    
    Laphony::Graphics::Engine gEngine("Test", 800,600, true, true);
        fEngine.Register(&gEngine);
    
    Laphony::Events::Engine evEngine(AUTOFREE);
        fEngine.Register(&evEngine);
        
    Laphony::BasicPhysic::Engine bpEngine;
        
    
    Laphony::Graphics::BasicText vtFps("FPS", {0,0}, 1.2, true);
    vtFps.SetPivot({0,0});
    
    gEngine.Register(&vtFps);
    
    TestText text("Je suis un test");
    gEngine.Register(&text);
    fEngine.Register(&text);
    
    TestGround ground(&gEngine);
    ground.Position({0,400});
    
    gEngine.Register(&ground);
    bpEngine.Register(&ground);
    
    TestGround wall1(&gEngine, 10, 100);
    wall1.Position({0, 200});
    
    gEngine.Register(&wall1);
    bpEngine.Register(&wall1);
    
    
    TestGround wall2(&gEngine, 100, 50);
    wall2.Position({200, 250});
    
    gEngine.Register(&wall2);
    bpEngine.Register(&wall2);
    
    Slope slope(&gEngine,100,50);
    slope.Position({400, 300});
    gEngine.Register(&slope);
    bpEngine.Register(&slope);
    
    TestCharacter character(&gEngine, &bpEngine);


    gEngine.Register(&character);
    fEngine.Register(&character,true);
    bpEngine.Register(&character);
   
    //Mappage keys
    evEngine.Register("move_left", new Laphony::Events::KeyControl("d"));
    evEngine.Register("move_right", new Laphony::Events::KeyControl("q"));
    
    evEngine.Register("Camera Up", new Laphony::Events::KeyControl("Up"));
    evEngine.Register("Camera Down", new Laphony::Events::KeyControl("Down"));
    evEngine.Register("Camera Left", new Laphony::Events::KeyControl("left"));
    evEngine.Register("Camera Right", new Laphony::Events::KeyControl("right"));

    
    evEngine.Register("move_hat",  new Laphony::Events::JoyHatControl(0,0));
    
    evEngine.Register("move_axis", new Laphony::Events::JoyAxisControl(0,0));
    
    evEngine.Register("joytest", new Laphony::Events::JoyButtonControl(0,0));
    
    Laphony::Events::KeyControl* keyPause = new Laphony::Events::KeyControl("p");
    evEngine.Register("pause", keyPause);
    
    evEngine.Register("jump", new Laphony::Events::KeyControl("space"));
    evEngine.Register("jump_joy", new Laphony::Events::JoyButtonControl(0,1));
    evEngine.Register("jump_mouse", new Laphony::Events::MouseButtonControl(Laphony::Events::MouseButtonControl::LEFT));
    
    std::vector<TestRectangle*> testRectangles;
    for(int i=0; i<00; i++)
    {
        TestRectangle* t = new TestRectangle(&gEngine);
        testRectangles.push_back(t);
        gEngine.Register(t);
        fEngine.Register(t);
    }
    
    
    Laphony::Frames::ThreadEngine thEngine(100, "Laphony->Test");
    
    TestCounterThread counterThread;
    thEngine.Register(&counterThread);
    
    //Must be the last
    fEngine.Register(&bpEngine);
        
    int lastFPS = 0;
    
    do
    { 
        
        
        if(fEngine.LastFPS() != lastFPS)
        {
            std::ostringstream oss;
            oss << "FPS: " << fEngine.LastFPS();
            vtFps.Text(oss.str());
            
            if(fEngine.LastFPS() < 10)
                vtFps.ColorText({255, 0, 0, 255});
            std::cout << vtFps.Text() << std::endl;
            lastFPS = fEngine.LastFPS();
        }
 
        counterThread.Print();
        
        Laphony::Rect camera = gEngine.Camera();
        
        if(evEngine.GetValueOf("Camera Up"))
        {
            //std::cout << character.Scale().x << ";" << character.Scale().y << std::endl;
            character.Scale({character.Scale().x, character.Scale().y + 0.01});
        }
            
        if(evEngine.GetValueOf("Camera Down"))
        {
            //std::cout << character.Scale().x << ";" << character.Scale().y << std::endl;
            character.Scale({character.Scale(). x, character.Scale().y - 0.01});
        }
            
        //std::cout << "Vel: " << character.GetVelocity().x << ";" << character.GetVelocity().y << std::endl;
            
       /* if(evEngine.GetValueOf("Camera left"))
            camera.x -=5;
        if(evEngine.GetValueOf("Camera right"))
            camera.x +=5;*/
        
        gEngine.Camera(camera); 
        
        if(evEngine.GetValueOf("Rotation right"))
            text.Angle(text.Angle()+2);
        if(evEngine.GetValueOf("Rotation Left"))
            text.Angle(text.Angle()-2);
      
        
        bool persoMove = false;
        
        if(evEngine.GetValueOf("jump") || evEngine.GetValueOf("jump_joy") || evEngine.GetValueOf("jump_mouse"))
        {
            //SDL_SetRenderDrawColor(gEngine.Renderer(), 0,0,255,255);
            character.Jump();
        }
        
            SDL_SetRenderDrawColor(gEngine.Renderer(), 0,0,0,255);
        
        if(evEngine.GetValueOf("move_hat") & Laphony::Events::JoyHatControl::LEFT || evEngine.GetValueOf("move_axis") < -5 || evEngine.GetValueOf("move_right"))
        {
            character.Move(true);
            persoMove = true;
            //character.Scale({-2,2});
        }
            
        if(evEngine.GetValueOf("move_hat") & Laphony::Events::JoyHatControl::RIGHT || evEngine.GetValueOf("move_axis") > 5 ||evEngine.GetValueOf("move_left"))
        {
            character.Move(false);
            persoMove = true;
            //character.Scale({2,2});
        }
        
            
        if(persoMove)
            character.SetCurrentAnimation("run");
        else
            character.SetCurrentAnimation("idle");
            
         
        
        fEngine.Update();
    }while(!evEngine.AppQuit());
    
    
    for(TestRectangle* t : testRectangles)
        if(t)
            delete t;
    
    return 0;
}

