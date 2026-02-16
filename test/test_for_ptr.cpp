//
// Created by Jeff Whynot on 2026/1/31.
//

#include <iostream>
#include "case_for_virtual.h"
#include <iomanip>

int main() {
    Animal *a1 = new Dog(); // dynamic allocate on heap
    a1->speak();
    delete a1;

    Animal a2 = Animal(); // real Animal obj
    a2.speak();

    int a = 10;
    int *p1 = nullptr;
    int *p2 = &a;
    int *p3 = new int(20);

    *p2 = 100;
    std::cout << *p2 << std::endl;
    p2 = p3;
    p2 = nullptr;

    const int* p4 = &a;
    int* const p5 = &a;
    const int* const p6 = &a;

    int nights = 1001;
    int *pt = new int;
    *pt = 1001;

    std::cout << nights << " : location :" << &nights << std::endl;
    std::cout << "int ";
    std::cout << "value = " << *pt << ": location : " << pt << std::endl;
    double* pd = new double;
    *pd = 10000001.0;
    std::cout << "double ";
    std::cout << "value = " << *pd << ": location : " << pd << std::endl;
    std::cout << "location of ptr pd: " << &pd << std::endl;
    std::cout << "size of ptr pt = " <<  sizeof(pt) << std::endl;
    std::cout << "size of ptr *pt = " <<  sizeof(*pt) << std::endl;
    std::cout << "size of ptr pd = " <<  sizeof(pd) << std::endl;
    std::cout << "size of ptr *pd = " <<  sizeof(*pd) << std::endl;

    int* px = new int(2);
    int* py = px;
    std::cout << "before delete *px = "<< *px << std::endl;
    delete py;
    std::cout << "after delete *px = "<< *px << std::endl;

    int* parrx = new int[100];
    delete[] parrx;
    int* parry = new int;
    short* ps = new short[100];
    delete[] ps;
    delete[] parry;

    double wages[3] = {10000.0, 20000.0, 30000.0};
    short stacks[3] = {3, 2, 1};
    double* pw = wages;
    short* pst = &stacks[0];
    std::cout << "pw = " << pw << " *pw = " << *pw << std::endl;
    pw = pw + 1;
    std::cout << "pw = " << pw << " *pw = " << *pw << std::endl;
    std::cout << "pst = " << pst << " *pst = " << *pst << std::endl;
    pst = pst + 1;
    std::cout << "pst = " << pst << " *pst = " << *pst << std::endl;
    std::cout << "stacks[0] = " << stacks[0] << " stacks[1] = " << stacks[1] << std::endl;
    std::cout << "*stacks = " << *stacks << " *stacks = " << "*(stacks + 1) = " << *(stacks + 1) << std::endl;
    std::cout << sizeof(wages) << " = size of wages array" << std::endl;
    std::cout << sizeof(pw) << " = size of pw ptr array" << std::endl;

    long double lda[3] = {1.000001, 2.000001, 3.000001};
    std::cout << std::setprecision(7);
    long double * plda = & lda[0];
    std::cout << plda << " " << plda + 1 << " " << plda + 2 << std::endl;
    std::cout << *plda << " " << *(plda + 1) << " " << *(plda + 2) << std::endl;

    std::cout << "OK" << std::endl;
    return 0;
}