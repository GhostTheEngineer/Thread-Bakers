/******************************************************************************
 * Project: Thread Bakers - Console App
 * File: step_3.cpp
 * Description:
 *   Implements mutual exclusion(mutex) for thread synchronization.
 *   Using chrono, it tracks how long the program takes.
 *
 * Copyright © 2025 Ghost - Two Byte Tech. All Rights Reserved.
 *
 * This source code is licensed under the MIT License. For more details, see
 * the LICENSE file in the root directory of this project.
 *
 * Version: v1.0.1
 * Author: Ghost
 * Created On: 02-17-2025
 * Last Modified: 02-21-2025
 *****************************************************************************/

#include <random>
#include <iomanip>

#include <thread>
#include <iostream>
#include <mutex> // NEW - library to create locks for thread synchronization

// NON TUTORIAL
int getRandomWorkTime() {
    static std::random_device rd;  // Random seed generator (hardware-based entropy source)
    static std::mt19937 gen(rd()); // Pseudo-random number generator (Mersenne Twister)
    std::uniform_int_distribution<int> dist(250, 500); // Range: quarter - half a second(milliseconds)
    return dist(gen);
}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


// Global variables
int piesPerBaker = 5;
int piesBaked = 0;
int noOfBakers = 4;
std::mutex mtx; // NEW - (mutual exclusion) thread synchronization - locking mechanism

void baker(int id) {

    for (int i = 0; i < piesPerBaker; i++)
    {
        int workTime = 0; // FIX - moved function call to protected lock below

        mtx.lock(); // NEW - lock to prevent other threads from accessing shared variables and operations to avoid race conditions
        workTime = getRandomWorkTime(); // FIX - static variables in functions must be thread protected since they are global
        std::cout << "...Baker " << id << " is making pie #" << (piesBaked + 1) << std::endl;
        piesBaked++;
        mtx.unlock(); // NEW - must remember to unlock!!

        std::this_thread::sleep_for(std::chrono::milliseconds(workTime));
    }
    
}

int main() {
    std::cout << "Bakery is preparing order.." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::thread baker1(baker, 1);
    std::thread baker2(baker, 2);
    std::thread baker3(baker, 3);
    std::thread baker4(baker, 4);

    baker1.join();
    baker2.join();
    baker3.join();
    baker4.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "\nResults\n   Total pies baked: " << piesBaked << "/" << (piesPerBaker * noOfBakers) << std::endl;
    std::cout << std::setprecision(2) << "   Total time: " << elapsed.count() << "s" << std::endl;

}
