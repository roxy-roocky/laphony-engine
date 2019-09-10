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
    
    Laphony::Frames::Engine fEngine(100);
    
    Laphony::Graphics::Engine gEngine("Test", 800,600, true, true);
        fEngine.Register(&gEngine);
    
    Laphony::Events::Engine evEngine(AUTOFREE);
        fEngine.Register(&evEngine);
        
    Laphony::BasicPhysic::Engine bpEngine;
        fEngine.Register(bpEngine);
    
    Laphony::Graphics::BasicText vtFps("FPS", {0,0}, 1.2, true);
    vtFps.Pivot({0,0});
    
    gEngine.Register(&vtFps);
    
    TestText text("Je suis un test");
    gEngine.Register(&text);
    fEngine.Register(&text);
    
    
    Laphony::Graphics::Animator anim;
    anim.Scale({2,2});
    
    anim.SetCurrentAnimation("idLE");
    
    anim.Position({200,400});
    
    anim.Register("run", new Laphony::Graphics::Animation(new Laphony::Graphics::Image("test/res/run-46-93.png",&gEngine),{0,0,46,93}, 10, AUTOFREE, {23,93}), AUTOFREE);
    anim.Register("idle", new Laphony::Graphics::Animation(new Laphony::Graphics::Image("test/res/idle-52-82.png",&gEngine),{0,0,52,82}, 14, AUTOFREE,  {26,82}), AUTOFREE);

    gEngine.Register(&anim);
    fEngine.Register(&anim);
   
    //Mappage keys
    evEngine.Register("Rotation Left", new Laphony::Events::KeyControl("Q"));
    evEngine.Register("Rotation Right", new Laphony::Events::KeyControl("D"));
    
    evEngine.Register("Camera Up", new Laphony::Events::KeyControl("Up"));
    evEngine.Register("Camera Down", new Laphony::Events::KeyControl("Down"));
    evEngine.Register("Camera Left", new Laphony::Events::KeyControl("left"));
    evEngine.Register("Camera Right", new Laphony::Events::KeyControl("right"));
    
    //evEngine.Register("left", new Laphony::Events::KeyControl("left"));
    //evEngine.Register("right", new Laphony::Events::KeyControl("right"));
    
    Laphony::Events::JoyHatControl* hat = new Laphony::Events::JoyHatControl(0,0);
    evEngine.Register("move", hat);
    
    Laphony::Events::JoyAxisControl* axis = new Laphony::Events::JoyAxisControl(0,0);
    evEngine.Register("move_axis", axis);
    
    Laphony::Events::JoyButtonControl* jb = new Laphony::Events::JoyButtonControl(0,0);
    evEngine.Register("joytest", jb);
    
    Laphony::Events::KeyControl* keyPause = new Laphony::Events::KeyControl("p");
    evEngine.Register("pause", keyPause);
    
    std::vector<TestRectangle*> testRectangles;
    for(int i=0; i<100; i++)
    {
        TestRectangle* t = new TestRectangle(&gEngine);
        testRectangles.push_back(t);
        gEngine.Register(t);
        fEngine.Register(t);
    }
    
        
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
 
        
        SDL_Rect camera = gEngine.Camera();
        
        if(evEngine.GetValueOf("Camera up"))
            anim.Scale({anim.Scale().x, anim.Scale().y + 0.01});
        if(evEngine.GetValueOf("Camera down"))
            anim.Scale({anim.Scale(). x, anim.Scale().y - 0.01});
       /* if(evEngine.GetValueOf("Camera left"))
            camera.x -=5;
        if(evEngine.GetValueOf("Camera right"))
            camera.x +=5;*/
        
        gEngine.Camera(camera); 
        
        if(evEngine.GetValueOf("RotaTIon right"))
            text.Angle(text.Angle()+2);
        if(evEngine.GetValueOf("Rotation Left"))
            text.Angle(text.Angle()-2);
      
        
        if(keyPause->Value() && !keyPause->LastValue())
            anim.Pause(!anim.Paused());
        
        bool persoMove = false;
        
        if(evEngine.GetValueOf("move") & Laphony::Events::JoyHatControl::LEFT || evEngine.GetValueOf("move_axis") < -5)
        {
            anim.Translate({-2,0});
            persoMove = true;
            anim.Scale({-2,2});
        }
            
        if(evEngine.GetValueOf("move") & Laphony::Events::JoyHatControl::RIGHT || evEngine.GetValueOf("move_axis") > 5)
        {
            anim.Translate({2,0});
            persoMove = true;
            anim.Scale({2,2});
        }
        
        if(jb->Value() != jb->LastValue())
        {
            std::cout << jb->ToString() << ": " << jb->Value() << std::endl;
        }
            
        if(persoMove)
            anim.SetCurrentAnimation("run");
        else
            anim.SetCurrentAnimation("idle");
            
        
        
        fEngine.Update();
        
    }while(!evEngine.AppQuit());
    
    
    for(TestRectangle* t : testRectangles)
        if(t)
            delete t;
    
    return 0;
}

