/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCounterThread.cpp
 * Author: nathan
 * 
 * Created on November 23, 2019, 2:14 PM
 */
#include <iostream>
#include "TestCounterThread.h"

TestCounterThread::TestCounterThread(): _c(0)
{

}

void TestCounterThread::Print() 
{
    Lock();
    std::cout << "TestCounterThread: " << _c << std::endl;
    Unlock();
}


void TestCounterThread::Update()
{
    _c++;
}

