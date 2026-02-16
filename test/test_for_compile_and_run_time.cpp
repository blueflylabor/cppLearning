#include <iostream>
#include <cassert>
#include <type_traits>


#define LEN 10  // Traditional macro, compile-time constant

int len_foo() {
    int i = 2;
    return i;  // Returns a value at runtime
}

constexpr int len_foo_constexpr() {
    return 5;  // Computed at compile time
}


template<typename T>
auto printTypeInfo(const T& t){
    if constexpr(std::is_integral<T>::value)
        return t + 1;
    else
        return t + 0.001;
}

void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {  // Value capture at runtime
        return value;  // Captures a copy of 'value' when lambda is created
    };
    value = 100;  // Change after lambda creation
    auto stored_value = copy_value();  // Calls at runtime, returns 1 (captured copy)
    std::cout << "stored_value = " << stored_value << std::endl;
}


int main(){
    std::cout << printTypeInfo(5) << std::endl;
    std::cout << printTypeInfo(3.14) << std::endl;


    // char arr_1[LEN];  // OK, LEN is compile-time constant
    // char arr_2[len_foo()];  // Error: len_foo() is runtime, can't determine size at compile time
    char arr_3[len_foo_constexpr()];  // OK, size computed at compile time

    lambda_value_capture();  // Outputs: stored_value = 1

    std::cout << "OK" << std::endl;
    return 0;
}