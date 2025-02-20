/******************************************************************************
 * Project: Thread Bakers - Console App
 * File: step_4.cpp
 * Description:
 *   Implements lock guard for automatic locking/unlocking and exception safety.
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
int noOfBakers = 4;
std::mutex mtx;

void baker(int id) {

    for (int i = 0; i < piesPerBaker; i++)
    {
        int workTime = getRandomWorkTime();

        { // NEW - scope for lock_guard
            /* Inner Scope Explained
                
                Why have inner scope?

                Lock Guard only unlocks the mutex once they go out of scope. Since each iteration has 
                a sleep/delay time, this will cause blocking - meaning other threads cannot
                continue because that is the nature of locking to prevent race conditions.

                Instead, we create a inner scope and place any global variables/operations in it, 
                except the sleep/delay function. This way we lock thread, adjust shared variable(piesBaked) 
                and operate shared object(cout), once end of scope reached, it unlocks allowing other
                threads to continue while this one sleeps. This promotes true multithreading by utilizing 
                threads properly.

            */
            std::lock_guard<std::mutex> lock(mtx); // NEW - automatic locking/unlocking and exceptions safety
            /* What is lock_guard again?
                
                This is a object that allows automatic locking and unlocking of mutex and handles any exceptions
                if they arise. Without it you must manually lock/unlock using

                    mtx.lock()

                    mtx.unlock()

                The constructor calls mtx.lock().
                The destructor calls mtx.unlock().

            */
            std::cout << "...Baker " << id << " is making pie #" << (piesBaked + 1) << std::endl;
            piesBaked++;
        }

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
