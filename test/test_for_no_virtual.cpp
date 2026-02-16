//
// Created by Jeff Whynot on 2026/1/29.
//

#include "case_for_no_virtual.h"

int main() {
    Animal *a1 = new Dog();
    Animal *a2 = new Cat();
    a1->speak();
    a2->speak();
    delete a1;
    delete a2;
    std::cout << "OK" << std::endl;
    return 0;
}