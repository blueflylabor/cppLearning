#include <iostream>
#include <memory>
#include <utility>
using namespace std;

void lambda_val_cap(){
    int val = 1;
    auto cp_val = [val]{
        return val;
    };
    val = 100;
    auto stored_val = cp_val();
    std::cout << "stored_val = " << stored_val << std::endl;
}

void lambda_ref_cap(){
    int val = 1;
    auto cp_val = [&val]{
        return val;
    };
    val = 100;
    auto stored_val = cp_val();
    std::cout << "stored_val = " << stored_val << std::endl;
}

void lambda_expr_cap(){
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)] (int x, int y) -> int {
        return x + y + v1 + (*v2);
    };
    std::cout << add(3, 4) << std::endl;
}

auto add = [](auto x, auto y){
    return x + y;
};



int main(){
    lambda_val_cap();
    lambda_ref_cap();
    lambda_expr_cap();
    std::cout << add(1, 2) << std::endl;
    std::cout << add(1, 2.2) << std::endl;




    cout << "OK" << endl;
    return 0;
}
