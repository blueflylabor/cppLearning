//
// Created by Jeff Whynot on 2026/1/31.
//

#include <iostream>
#include "case_for_virtual.h"

void func1(int x) {
    x = 100;
}

void func2(int* x) {
    *x = 100;
}

void func3(int& x) {
    x = 100;
}

int main() {
    int a = 10;
    int& r1 = a;
    int& r2 = r1;
    std::cout << a << std::endl;
    r1 = 999;
    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;

    int x,y;
    x = 5;
    y = 6;
    int& ref = x;
    ref = y; // not change of ref, copy y->ref->x
    std::cout << ref << std::endl;
    std::cout << x << std::endl;

    const int& r = 100;

    int u, v, w;
    u = 10;
    v = 10;
    w = 10;
    std::cout << u << " " << v << " " << w << std::endl;
    int* v_ptr = &v;
    func1(u);
    func2(v_ptr);
    func3(w);
    std::cout << u << " " << v << " " << w << std::endl;

    // int* p = nullptr;
    // *p = 10;



    std::cout << "OK" << std::endl;
    return 0;
}