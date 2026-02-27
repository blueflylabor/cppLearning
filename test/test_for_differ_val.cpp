#include <iostream>
#include <utility>

class Res{
    public:
        int* data;
        Res(): data(new int(100)){}
        // ~Res(){delete data;}
};

Res getRes(){
    Res r;
    return r;
}

int getVal(){
    return 42; // return pure right val (temporary int)
}

void func(int&& rv){ // rv binds to rval
    std::cout << rv << std::endl;
}

int main(){
    int x = 10; // lval
    int& ref = x; //bind to lval ref    
    std::cout << &x << std::endl;   // take addr of lval
    std::cout << "before changed : " << x << std::endl;
    x = 20; // assign to lval
    std::cout << "after changed : " << x << std::endl;

    int y = 5 + 3; // 5 + 3 is prval, initializes y
    int z = getVal();
    
    Res r;
    Res moved_r = std::move(r); //std::move(r) is xval, allows moving res
    std::cout << "moved r : " <<r.data << std::endl;  // after move, r.data may be null

    int l = 10;
    auto& ref_l = l; // ref binds to glval
    auto&& moved_l = std::move(l); // moved binds to glval

    func(42); // 42 is prval
    int a = 10;
    func(std::move(a)); // std::move(a) is xval


    std::cout << "OK" << std::endl;
    return 0;
}