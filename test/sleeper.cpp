/* 
 * File:   sleeper.cpp
 * Author: alex
 *
 * Created on June 8, 2017, 1:41 PM
 */

#include <chrono>
#include <iostream>
#include <thread>

int main() {
    std::cout << "Preparing a pillow ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Wake up!" << std::endl;
    return 0;
}

