/******************************************************************************
 * Project: Thread Bakers - Console App
 * File: step_5.cpp
 * Description:
 *   Implements 4 additional threads to speed up the process of baking 20 pies. 
 *   Using chrono, it tracks how long the program takes.
 *
 * Copyright © 2025 Ghost - Two Byte Tech. All Rights Reserved.
 *
 * This source code is licensed under the MIT License. For more details, see
 * the LICENSE file in the root directory of this project.
 *
 * Version: v1.0.0
 * Author: Ghost
 * Created On: 02-17-2025
 * Last Modified: 02-17-2025
 *****************************************************************************/

#include <random>
#include <iomanip>

#include <thread>
#include <iostream>
#include <mutex> 

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
int piesNeeded = 20; // NEW - limit to a total of 20 pies to bake
int noOfBakers = 8; // NEW - updated from 4 to 8 (note, output will show 20/40 - meaning these bakers are capable of baking 80 but limited to 20)
std::mutex mtx;

void baker(int id) {

    for (int i = 0; i < piesPerBaker; i++)
    {
        int workTime = getRandomWorkTime();

        { 
            std::lock_guard<std::mutex> lock(mtx);
            
            if (piesBaked == piesNeeded) break; // NEW - if reached goal, break out of the thread early

            std::cout << "...Baker " << id << " is making pie #" << (piesBaked + 1) << std::endl;
            piesBaked++;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(workTime));
    }
    
}

int main() {
    std::cout << "Bakery is preparing order.." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    // NEW - Bigger kitchen allows 4 bakers to bake at the same time(4 parallel threads)
    std::thread baker1(baker, 1);
    std::thread baker2(baker, 2);
    std::thread baker3(baker, 3);
    std::thread baker4(baker, 4);
    std::thread baker5(baker, 5);
    std::thread baker6(baker, 6);
    std::thread baker7(baker, 7);
    std::thread baker8(baker, 8);

    // NEW - ensure main thread knows about extra bakers(threads) and waits for them
    baker1.join();
    baker2.join();
    baker3.join();
    baker4.join();
    baker5.join();
    baker6.join();
    baker7.join();
    baker8.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "\nResults\n   Total pies baked: " << piesBaked << "/" << (piesPerBaker * noOfBakers) << std::endl;
    std::cout << std::setprecision(2) << "   Total time: " << elapsed.count() << "s" << std::endl;

}
