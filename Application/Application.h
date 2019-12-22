/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Application.h
 * Author: nathan
 *
 * Created on December 19, 2019, 10:50 PM
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Graphics/Engine.h"
#include "../Events/Engine.h"
#include "../Frames/Engine.h"

#include <stack>

namespace Laphony
{
    class Module;
    
    class Application 
    {
        public:
            Application();

        private:
            
            std::stack<Module*> _modules;
            
            Graphics::Engine _gEngine;
            Events::Engine _evEngine;
            Frames::Engine _fEngine;
    };
}

#endif /* APPLICATION_H */

