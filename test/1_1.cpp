#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    [out = std::ref(std::cout << "Result from C code: " << add(1, 2))](){
        out.get() << ".\n";
    }();
    std::cout << "OK" << std::endl;
    return 0;
}