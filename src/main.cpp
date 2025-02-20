/******************************************************************************
 * Project: Thread Bakers - Console App
 * File: main.cpp
 * Description:
 *   Implements multithreading and thread synchronization with a total of  
 *   8 threads to speed up the process of baking 20 pies.
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

#include <random> // for random number generating
#include <iomanip> // used for setprecision
#include <iostream>

#include <thread> // library to create threads
#include <mutex> // library to create locks for thread synchronization

// NON TUTORIAL
int getRandomWorkTime() {
    static std::random_device rd;  // Random seed generator (hardware-based entropy source)
    static std::mt19937 gen(rd()); // Pseudo-random number generator (Mersenne Twister)
    std::uniform_int_distribution<int> dist(250, 500); // Range: quarter - half a second(milliseconds)
    return dist(gen);
}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Global Variables
int piesPerBaker = 5; // represents how many pies ONE baker can bake
int piesBaked = 0; // represents the total pies baked
int noOfBakers = 8; // represents the number of bakers
std::mutex mtx; // (mutual exclusion) thread synchronization - locking mechanism
int piesNeeded = 20; // represents the number of bake pie limit - used to stop all bakers once reached

void baker(int id) {
    for(int i = 0; i < piesPerBaker; i++) { // each iteration is one pie baked
        int workTime = getRandomWorkTime(); // get random time in milliseconds

        {
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
            std::lock_guard<std::mutex> lock(mtx); 
            /* What is lock_guard again?

                This is a object that allows automatic locking and unlocking of mutex and handles any exceptions
                if they arise. Without it you must manually lock/unlock using

                    mtx.lock()

                    mtx.unlock()

                The constructor calls mtx.lock().
                The destructor calls mtx.unlock().

            */

            if (piesBaked == piesNeeded) return; // return early once goal is met - all bakers(threads) will stop working
        
            std::cout << "...Baker" << id << " is making pie #" << (piesBaked + 1) << std::endl;
            piesBaked++;

        } // unlock mtx automatically
        
        std::this_thread::sleep_for(std::chrono::milliseconds(workTime)); // simulated work time - varied
    } 
}

int main() {
    std::cout << "Bakery is preparing order..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now(); // record current time

    // Create and run 8 bakers(threads)
    std::thread baker1(baker, 1);
    std::thread baker2(baker, 2);
    std::thread baker3(baker, 3);
    std::thread baker4(baker, 4);
    std::thread baker5(baker, 5);
    std::thread baker6(baker, 6);
    std::thread baker7(baker, 7);
    std::thread baker8(baker, 8);
    
    // Main thread will wait for all bakers(threads) to return before continuing
    baker1.join();
    baker2.join();
    baker3.join();
    baker4.join();
    baker5.join();
    baker6.join();
    baker7.join();
    baker8.join();
    
    auto end = std::chrono::high_resolution_clock::now(); // record current time
    std::chrono::duration<double> elapsed = end - start; // calculate time it took for all bakers to bake 20 pies

    std::cout << "\nResults\n   Total pies baked: " << piesBaked << "/" << (piesPerBaker * noOfBakers) << std::endl;
    std::cout << std::setprecision(2) << "   Total time: " << elapsed.count() << "s" << std::endl;

    system("pause"); // prevent terminal from closing until user presses enter

    return 0;
}
