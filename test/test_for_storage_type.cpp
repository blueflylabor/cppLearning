//
// Created by Jeff Whynot on 2026/2/3.
//

#include <iostream>
#include <cstring>
#include <string>
char* bad_get_name() {
    char temp[20];
    strcpy(temp, "bad_get_name");
    return temp;
}

std::string* create_name() {
    std::string* p = new std::string("create_name");
    return p;
}

std::unique_ptr<std::string> create_name_modern() {
    return std::make_unique<std::string>("create_name_modern");
}

void safe_use() {
    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        sum += i;
    }
}

void func(){
    int a = 10; // automatic storage duration variable, created and destroyed within function scope
}

int global_count = 0; //static storage duration variable, whole program lifetime

void counter() {
    static int call_times = 0; // only initialized once, retains value between calls, not destroyed after function ends
    call_times++;
    std::cout << "The " << call_times << " times." << std::endl;
}

int main () {

    int *p = new int(42); // dynamic storage duration variable, created on heap
    delete p; // must be manually deleted to avoid memory leak

    char* name1 = bad_get_name();
    std::cout << name1 << std::endl;
    std::string* name2= create_name();
    std::cout << *name2 << std::endl;
    delete name2;
    name2 = nullptr;
    auto name3 = create_name_modern();
    std::cout << *name3 << std::endl;
    counter();
    counter();
    counter();
    std::cout << "OK" << std::endl;


    return 0;
}