//
// Created by Jeff Whynot on 2026/1/29.
//

#ifndef CPPLEARNING_CASE_FOR_NO_VIRTUAL_H
#define CPPLEARNING_CASE_FOR_NO_VIRTUAL_H


#include <iostream>

class Animal {
public:
    void speak() {
        std::cout << "shout!" << std::endl;
    }
};

class Dog : public Animal{
public:
    void speak() {
        std::cout << "wang!" << std::endl;
    }
};

class Cat: public Animal {
public:
    void speak() {
        std::cout << "miao!" << std::endl;
    }
};


#endif //CPPLEARNING_CASE_FOR_NO_VIRTUAL_H