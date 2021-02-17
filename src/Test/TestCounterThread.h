/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCounterThread.h
 * Author: nathan
 *
 * Created on November 23, 2019, 2:14 PM
 */

#ifndef TESTCOUNTERTHREAD_H
#define TESTCOUNTERTHREAD_H

#include "../Frames/ThreadUpdatable.h"

class TestCounterThread: public Laphony::Frames::ThreadUpdatable
{
    public:
        TestCounterThread();
        virtual void Update() override;
        
        void Print();

    private:
        int _c;

};

#endif /* TESTCOUNTERTHREAD_H */

