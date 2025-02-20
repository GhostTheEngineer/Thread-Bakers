/******************************************************************************
 * Project: Thread Bakers - Console App
 * File: step_2.cpp
 * Description:
 *   Implements parallel processing but introduces race conditions.
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

void baker(int id) {

    for (int i = 0; i < piesPerBaker; i++)
    {
        int workTime = getRandomWorkTime();
        std::cout << "...Baker " << id << " is making pie #" << (piesBaked + 1) << std::endl;
        piesBaked++;

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

    // NEW - main thread waits for each baker to finish before continuing
    baker1.join();
    baker2.join();
    baker3.join();
    baker4.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "\nResults\n   Total pies baked: " << piesBaked << "/" << (piesPerBaker * noOfBakers) << std::endl;
    std::cout << std::setprecision(2) << "   Total time: " << elapsed.count() << "s" << std::endl;

}
