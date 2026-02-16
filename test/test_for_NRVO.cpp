//
// Created by Jeff Whynot on 2026/2/4.
//
#include <iostream>
#include <cstring>
using namespace std;

char* bad_get_name() {
    char temp[20];
    strcpy(temp, "bad_get_name");
    return temp;
}

char* bad_get_name_move() {
    char temp[20];
    strcpy(temp, "bad_get_name_move");
    return std::move(temp);
}

char* bad_name() {
    char temp[20] = "bad_name";
    return temp;
}

int* bad_int() {
    int x[10] = {1,2,3,4,5,6,7,8,9,10};
    return x;
}

string good_get_name() {
    string temp = "good_get_name";
    return temp;
}

int* bad() {
    int x = 100;
    return &x;
}

char* worse() {
    char buf[100];
    strcpy(buf, "worse");
    return buf;
}


int main() {
    char* p1 = bad_get_name();
    string s1 = good_get_name();
    char* p2 = bad_name();
    int* p3 = bad_int();
    char* p4 = bad_get_name_move();
    cout << "*p1 = " << *p1 << std::endl;
    cout << "*p2 = " << *p2 << std::endl;
    cout << "s1 = " << s1 << std::endl;
    cout << "*p3 = " << *p3 << std::endl;
    cout << "*p4 = " << *p4 << std::endl;
    int* x = bad();
    char* w = worse();
    cout << "w = " << w << std::endl;
    cout << "x = " << x << std::endl;
    std::cout << "OK" << std::endl;


}
