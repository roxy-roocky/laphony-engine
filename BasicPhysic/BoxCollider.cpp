/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   BasicPhysic/BoxCollider.h
 * \author Nathan Baumann
 *
 * \date September 2, 2019, 10:42 PM
 */

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "MultiCollider.h"

namespace Laphony
{
    namespace BasicPhysic
    {

        BoxCollider::BoxCollider(const std::string& tag): Collider(tag)
        {

        }
        
        bool BoxCollider::CollisionWith(Collider* collider)
        {
            return collider->CheckCollision(this);
        }
        
        Rect BoxCollider::ComputeRealBox() const
        {
            Rect realBox = _box;
            realBox.x += _position.x;
            realBox.y += _position.y;
            realBox.w *= std::abs(_scale.x);
            realBox.y *= std::abs(_scale.y);
        }
        
        
        //CHECK
        bool BoxCollider::CheckCollision(BoxCollider* collider) const 
        {
            if(!collider)
                return false;
            
            Rect realBox = ComputeRealBox();
            Rect realOtherBox = collider->ComputeRealBox();
            
            
            return  
                //Check if a corner of this box is in the other box
                (
                    //Left Top
                    (realBox.x >= realOtherBox.x && realBox.x <= realOtherBox.x + realOtherBox.w && realBox.y >= realOtherBox.y && realBox.y <= realOtherBox.y + realOtherBox.h) ||
                    //Left Bottom
                    (realBox.x >= realOtherBox.x && realBox.x <= realOtherBox.x + realOtherBox.w && realBox.y + realBox.h >= realOtherBox.y && realBox.y + realBox.h <= realOtherBox.y + realOtherBox.h) ||
                    //Right Bottom
                    (realBox.x + realBox.w >= realOtherBox.x && realBox.x + realBox.w <= realOtherBox.x + realOtherBox.w && realBox.y + realBox.h >= realOtherBox.y && realBox.y + realBox.h <= realOtherBox.y + realOtherBox.h) ||
                    //Right Top
                    (realBox.x + realBox.w >= realOtherBox.x && realBox.x + realBox.w <= realOtherBox.x + realOtherBox.w && realBox.y >= realOtherBox.y && realBox.y <= realOtherBox.y + realOtherBox.h)
                ) 
                    
                ||
                //Check if a corner of the other box is in this box
                (
                    //Left Top
                    (realOtherBox.x >= realBox.x && realOtherBox.x <= realBox.x + realBox.w && realOtherBox.y >= realBox.y && realOtherBox.y <= realBox.y + realBox.h) ||
                    //Left Bottom
                    (realOtherBox.x >= realBox.x && realOtherBox.x <= realBox.x + realBox.w && realOtherBox.y + realOtherBox.h >= realBox.y && realOtherBox.y + realOtherBox.h <= realBox.y + realBox.h) ||
                    //Right Bottom
                    (realOtherBox.x + realOtherBox.w >= realBox.x && realOtherBox.x + realOtherBox.w <= realBox.x + realBox.w && realOtherBox.y + realOtherBox.h >= realBox.y && realOtherBox.y + realOtherBox.h <= realBox.y + realBox.h) ||
                    //Right Top
                    (realOtherBox.x + realOtherBox.w >= realBox.x && realOtherBox.x + realOtherBox.w <= realBox.x + realBox.w && realOtherBox.y >= realBox.y && realOtherBox.y <= realBox.y + realBox.h)
                );
                    
            
        }

        bool BoxCollider::CheckCollision(CircleCollider* collider) const
        {
            if(!collider)
                return false;
            
            Rect realBox = ComputeRealBox();
            Point realCenter = collider->ComputeRealCenter();
            int realRadius = collider->ComputeRealRadius();
            
            bool pointInBox, cornerInCircle;
            
            pointInBox = 
                //Check if a cardianal point of the circle is in this box
                (
                    //Nord
                    (realCenter.x >= realBox.x && realCenter.x <= realBox.x + realBox.w && realCenter.y - realRadius >= realBox.y && realCenter.y - realRadius <= realBox.y + realBox.h) ||
                    //South
                    (realCenter.x >= realBox.x && realCenter.x <= realBox.x + realBox.w && realCenter.y + realRadius >= realBox.y && realCenter.y + realRadius <= realBox.y + realBox.h) ||
                     //West
                    (realCenter.x - realRadius >= realBox.x && realCenter.x - realRadius <= realBox.x + realBox.w && realCenter.y >= realBox.y && realCenter.y <= realBox.y + realBox.h) ||
                    //East
                    (realCenter.x + realRadius >= realBox.x && realCenter.x + realRadius <= realBox.x + realBox.w && realCenter.y >= realBox.y && realCenter.y <= realBox.y + realBox.h) 
                );
            
            if(!pointInBox)
            {
                cornerInCircle =
                        (
                            //Left Top
                            (std::sqrt(std::pow(realBox.x-realCenter.x, 2) + std::pow(realBox.y-realCenter.y, 2)) >= realRadius) ||
                            //Left Bottom
                            (std::sqrt(std::pow(realBox.x-realCenter.x, 2) + std::pow(realBox.y+realBox.h-realCenter.y, 2)) >= realRadius) ||
                            //Right Top
                            (std::sqrt(std::pow(realBox.x+realBox.w-realCenter.x, 2) + std::pow(realBox.y-realCenter.y, 2)) >= realRadius) ||
                            //Right Bottom
                            (std::sqrt(std::pow(realBox.x+realBox.w-realCenter.x, 2) + std::pow(realBox.y+realBox.h-realCenter.y, 2)) >= realRadius) 
                        );
            }
            
            return pointInBox || cornerInCircle;
        }
        
        
        
        bool BoxCollider::CheckCollision(MultiCollider* collider) const
        {
            //Implement in MultipleCollider
            return collider->CollisionWith(this);
        }

    }
}


