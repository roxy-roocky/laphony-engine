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

namespace Laphony
{
    namespace Sound
    {
        Speaker::Speaker(Engine* engine): _engine(engine), _volume(255), _channel(-1), _onListener(true) 
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
        
        void Speaker::SetMaxAudibleDistance(uint32_t maxDistance) const 
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
                    distance = (distance/255.0) * _maxDistance;
                    double angle = std::asin((l.x-t.x)/distance);
                    
                    Mix_SetPosition(_channel, angle, distance);
                    
                    std::cout << "== Speaker pos calculation ==" <<std::endl;
                    std::cout << "Position listener: " << l << std::endl;
                    std::cout << "Position speaker: " << t << std::endl;
                    
                    std::cout << "Angle: " << angle << " Distance: " << distance << std::endl;
                }
            }
        }
    }
}

