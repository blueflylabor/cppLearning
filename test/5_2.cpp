#include <iostream>
#include <memory>

void foo(std::shared_ptr<int> i){
    (*i)++;
}

int main(){
    auto p = std::make_shared<int>(10);
    foo(p);
    std::cout << *p << std::endl;
    
    auto pp = p;
    auto ppp = p;
    int* ptr = p.get();
    std::cout << "p.use_count() = " << p.use_count() << std::endl;
    std::cout << "pp.use_count() = " << pp.use_count() << std::endl;
    std::cout << "ppp.use_count() = " << ppp.use_count() << std::endl;

    pp.reset();
    std::cout << "reset pp : " << std::endl;
    std::cout << "p.use_count() = " << p.use_count() << std::endl;
    std::cout << "pp.use_count() = " << pp.use_count() << std::endl;
    std::cout << "ppp.use_count() = " << ppp.use_count() << std::endl;

    ppp.reset();
    std::cout << "p.use_count() = " << p.use_count() << std::endl;
    std::cout << "pp.use_count() = " << pp.use_count() << std::endl;
    std::cout << "ppp.use_count() = " << ppp.use_count() << std::endl;



    std::cout << "OK" << std::endl;
    return 0;
}