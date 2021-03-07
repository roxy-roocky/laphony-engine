/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */
/* 
 * File:   newmain.cpp
 * Author: Nathan Baumann
 *
 * Created on June 20, 2019, 8:19 PM
 */

#define SCREEN_W 1280 
#define SCREEN_H 720

#include "Graphics/Engine.h"
#include "Frames/Engine.h"
#include "Events/Engine.h"
#include "Graphics/BasicText.h"
#include "Graphics/Image.h"

#include <sstream>
#include <iomanip>

using namespace Laphony;

/*
 * 
 */
int main(int argc, char** argv)
{
    Graphics::Engine gEngine("Test Android", SCREEN_W,SCREEN_H, true, true);
    SDL_RenderSetIntegerScale(gEngine.Renderer(), SDL_FALSE);
    SDL_SetWindowFullscreen(gEngine.Window(),SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    Frames::Engine fEngine(100);
    
    Events::Engine evEngine(true);
    
    
    fEngine.Register(&gEngine);
    fEngine.Register(&evEngine);
    
    //Fix very odd bug.
    Graphics::BasicText bug1("Laphony Engine runs",{1,50}, 4.0, true, {0,0,0,255});
    Graphics::BasicText bug2("Laphony Engine runs",{1,50}, 4.0, true, {0,0,0,255});
    
    Graphics::BasicText txtTest("Laphony Engine runs",{1,50}, 4.0, true, {0,0,0,255});
    
#ifdef ANDROID
    Graphics::BasicText txt2Test("on phone !!",{1,100}, 4.0, true, {0,0,0,255});
#else
    #ifdef WINDOWS
    Graphics::BasicText txt2Test("on Windows !!",{1,100}, 4.0, true, {0,0,0,255});
    #else
    Graphics::BasicText txt2Test("on linux !!",{1,100}, 4.0, true, {0,0,0,255});
    #endif
#endif
    gEngine.Register(&txtTest);
    gEngine.Register(&txt2Test);

    std::map<int64_t, Graphics::BasicText*> outFingers;
    
    Graphics::BasicText* imgJoyAccelName = nullptr;
   
    Graphics::Image imgBg(SCREEN_W,SCREEN_H,{255,255,255,255}, &gEngine);
    imgBg.Pivot({0,0});
    gEngine.Register(&imgBg);
    
    while(!evEngine.AppQuit())
    {
        fEngine.Update(true);
        
        //Fingers
        Events::Engine::FingerInfo finger = evEngine.PollTouchEvent();
        while(finger.type != Events::Engine::TouchEventType::NONE)
        {
            Graphics::BasicText* out;
            if(outFingers.find(finger.fingerID) != outFingers.end())
            {
                out = outFingers[finger.fingerID];
                gEngine.Unregister(out);
                delete out;
            }
            
            std::ostringstream oss;
            oss << "Finger id " << finger.fingerID << " state " << finger.type << " (" << std::fixed << std::setprecision(3) << finger.x << " ; " << finger.y << ")";
            
            out = new Graphics::BasicText(oss.str(),{0,0}, 4.0, true, {0,0,0,255});
            outFingers[finger.fingerID] = out;
            out->Position({1,200 + (50 * static_cast<double>(std::distance(outFingers.begin(),outFingers.find(finger.fingerID))))});
            gEngine.Register(out, true);
            
            finger = evEngine.PollTouchEvent();
        }
        
        //Accel
        Events::Engine::JoyInfo* joyAccel = evEngine.GetJoystickInfo(0);
        if(joyAccel)
        {
            std::ostringstream ossJoy;
            
            ossJoy << SDL_JoystickName(joyAccel->joy) << ":(" << std::fixed << std::setw(4) << std::setprecision(1) << SDL_JoystickGetAxis(joyAccel->joy, 0)/(float)INT16_MAX << "; " << std::setw(4) << SDL_JoystickGetAxis(joyAccel->joy, 1)/(float)INT16_MAX << "; " << std::setw(4) << SDL_JoystickGetAxis(joyAccel->joy, 2)/(float)INT16_MAX << ")";
            
            if(imgJoyAccelName)
            {
                gEngine.Unregister(imgJoyAccelName);
                delete imgJoyAccelName;
            }
            
            imgJoyAccelName = new Graphics::BasicText(ossJoy.str(), {1,150},4.0, true, {0,0,0,255});
            gEngine.Register(imgJoyAccelName, true);
        }
    }
    
    if(imgJoyAccelName)
    {
        gEngine.Unregister(imgJoyAccelName);
        delete imgJoyAccelName;
    }
    
    for(auto img: outFingers)
    {
        if(img.second)
        {
            gEngine.Unregister(img.second);
            delete img.second;
        }
    }
    
    return 0;
}

