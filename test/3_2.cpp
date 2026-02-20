#include <iostream>
#include <functional>

using foo_ = void(int);
void functional(foo_ f){
    f(1);
}

int foo(int para){
    return para;
}

int foo1(int a, int b, int c){
    ;
}

int main(){
    auto f = [](int val){
        std::cout << val << std::endl;
    };
    functional(f);

    std::function<int(int)> func1 = foo;
    int important = 10;
    std::function<int(int)> func2 = [&](int val) -> int{
        return 1 + val + important;
    };
    std::cout << func1(10) << std::endl;
    std::cout << func2(10) << std::endl;

    auto bindFoo = std::bind(foo, std::placeholders::_1, 1,2);
    
    std::cout << "OK" << std::endl;
    return 0;
}