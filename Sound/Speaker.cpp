/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DedicatedChannel.cpp
 * Author: nathan
 * 
 * Created on December 23, 2019, 4:53 PM
 */

#include <iostream>

#include "Speaker.h"

#include "Engine.h"
#include "Sound.h"

namespace Laphony
{
    namespace Sound
    {
        Speaker::Speaker(Engine* engine): _engine(engine), _volume(255), _channel(-1), _onListener(true), _maxDistance(255) 
        {
            if(_engine)
            {
                _channel = engine->GetFirstAvailableChannel();
                _engine->_channelsDedicated[_channel] = true;
            }
        }
        
        Speaker::~Speaker()
        {
            if(_engine)
            {
                _engine->_channelsDedicated[_channel] = false;
            }
        }
        
        void Speaker::Play(const std::string& name)
        {
            Sound* snd = _engine->_sounds[name];
            if(!Mix_Playing(_channel))
                Mix_PlayChannel(_channel,snd->_sound,0);
        }
        
        bool Speaker::IsStickOnListener() const 
        {
            return _onListener;
        }
        
        void Speaker::StickOnListener(bool stick) 
        {
            _onListener = stick;
            if(stick)
            {
                Mix_SetPosition(_channel,0,0);
            }
            else
            {
                Position(Position());//fake move for set audio position
            }
        }

        Point Speaker::Position() const
        {
            return Transformable::Position();
        }
        
        uint32_t Speaker::GetMaxAudibleDistance() const 
        {
            return _maxDistance;
        }
        
        void Speaker::SetMaxAudibleDistance(uint32_t maxDistance) 
        {
            _maxDistance = maxDistance;
        }


        void Speaker::Position(const Point& point)
        {
            Transformable::Position(point);
            if(!IsStickOnListener() && _engine)
            {
                Transformable* listener = _engine->GetListener();
                if(listener)
                {
                    Point l = listener->Position();
                    Point t = Position();
                    
                    double distance = std::sqrt(std::pow(l.x - t.x , 2) + std::pow(l.y - t.y , 2));
                    
                    double angle = 0;
                    
                    if(distance != 0)
                        angle = (std::asin((l.x-t.x)/distance) / (M_PI)) * 360;
                    
                    angle += 180;
                    
                    //compute real distance (proportion of maxDistance 
                    distance = (double)(distance/(double)_maxDistance) * 255.0;
                    
                    Mix_SetPosition(_channel, angle, distance < 0 ? 0 : distance > 255 ? 255 : distance);
                    
                    std::cout << "== Speaker pos calculation ==" <<std::endl;
                    std::cout << "Position listener: " << l << std::endl;
                    std::cout << "Position speaker: " << t << std::endl;
                    
                    std::cout << "RAD! " << std::asin((l.x-t.x)/distance) << std::endl;
                    std::cout << "Angle: " << angle << " Distance: " << distance << std::endl;
                }
            }
        }
    }
}

