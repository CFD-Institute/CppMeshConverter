/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExecutionTimer.h
 * Author: Truong
 *
 * Created on July 8, 2021, 10:40 PM
 */

#ifndef EXECUTION_TIMER_H
#define EXECUTION_TIMER_H

#include <chrono>
#include <sstream>

using namespace std;

template<class Resolution = std::chrono::milliseconds>
class ExecutionTimer {

private:
    const std::chrono::high_resolution_clock::time_point mStart = std::chrono::high_resolution_clock::now();

public:
    ExecutionTimer() = default;
    ~ExecutionTimer() {
        const auto end = std::chrono::high_resolution_clock::now();
        std::ostringstream strStream;
        strStream << "Destructor Elapsed: " 
                << std::chrono::duration_cast<Resolution>( end - mStart ).count()
                << " miliSeconds."
                << std::endl;
        std::cout << strStream.str() << std::endl;
    }    

    inline void stop() {
        const auto end = std::chrono::high_resolution_clock::now();
        std::ostringstream strStream;
        strStream << "Stop Elapsed: "
                << std::chrono::duration_cast<Resolution>(end - mStart).count() 
                << " miliSeconds."  
                << std::endl;
        std::cout << strStream.str() << std::endl;
    }

}; // ExecutionTimer

#endif // EXECUTION_TIMER_H

