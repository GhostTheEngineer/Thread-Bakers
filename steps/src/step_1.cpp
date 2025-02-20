
/******************************************************************************
 * Project: Thread Bakers - Console App
 * File: step_1.cpp
 * Description:
 *   Implements sequential processing where 4 bakers will bake 5 pies for a total
 *   of 20. Using chrono, it tracks how long the program takes.
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

#include <thread> // library to create threads
#include <iostream>

// NON TUTORIAL
int getRandomWorkTime() {
    static std::random_device rd;  // Random seed generator (hardware-based entropy source)
    static std::mt19937 gen(rd()); // Pseudo-random number generator (Mersenne Twister)
    std::uniform_int_distribution<int> dist(250, 500); // Range: quarter - half a second(milliseconds)
    return dist(gen);
}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


// Global variables
int piesPerBaker = 5; // set to some amount of pies each baker will make
int piesBaked = 0; // track how many pies were baked
int noOfBakers = 4; // set to number of times we call baker function

// Each call is one baker working
void baker(int id) {

    for (int i = 0; i < piesPerBaker; i++) { // each iteration is one pie baked
        int workTime = getRandomWorkTime(); // get random time in milliseconds
        
        std::cout << "...Baker " << id << " is making pie #" << (piesBaked + 1) << std::endl;
        piesBaked++;

        std::this_thread::sleep_for(std::chrono::milliseconds(workTime)); // simulated work time - varied
    }
    
}

int main() {
    std::cout << "Bakery is preparing order.." << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now(); // record current time

    // We call baker 4 times because we need 20 pies, each baker must wait for the other to finish to start baking
    baker(1); 
    baker(2); 
    baker(3); 
    baker(4); 

    auto end = std::chrono::high_resolution_clock::now(); // record current time
    std::chrono::duration<double> elapsed = end - start; // calculate time it took for all bakers to bake 20 pies

    std::cout << "\nResults\n   Total pies baked: " << piesBaked << "/" << (piesPerBaker * noOfBakers) << std::endl;
    std::cout << std::setprecision(2) << "   Total time: " << elapsed.count() << "s" << std::endl;

}
