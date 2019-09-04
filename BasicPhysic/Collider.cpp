
/*
 * This file is a part of the Laphony Engine.
 * Copyright 2019 Nathan Baumann. All rights reserved.
 */

/* 
 * \file   BasicPhysic/Collider.cpp
 * \author Nathan Baumann
 *
 * \date august 29 2019, 5:19 PM
 */

#include "Collider.h"

namespace Laphony
{
    namespace BasicPhysic
    {
        Collider::Collider(std::string const& tag): _tag(tag)
        {
            
        }
        
        std::string Collider::GetTag() const 
        {
            return _tag;
        }
        
        void Collider::SetTag(std::string const& tag)
        {
            _tag = tag;
        }
    }
}

