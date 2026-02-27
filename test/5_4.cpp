#include <iostream>

struct A;
struct B;

struct A{
    std::shared_ptr<B> ptr;
    ~A(){
        std::cout << "A has been destroyed." << std::endl;
    }
};

struct B
{
    std::shared_ptr<A> ptr;
    ~B(){
        std::cout << "B has been destroyed." << std::endl;
    }
};


int main(){

    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->ptr = b;
    b->ptr = a;


    std::cout << "OK" << std::endl;
    return 0;
}