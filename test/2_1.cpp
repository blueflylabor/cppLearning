#include <iostream>
#include <type_traits>
#include <cassert>
#define LEN 10
void foo(char *);
void foo(int);
int len_foo();
constexpr int len_foo_constexpr();
constexpr int fibonacci(const int n);

int main(){
    if (std::is_same<decltype(NULL), decltype(0)>::value)
        std:: cout << "NULL == 0" << std::endl;
    if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
        std::cout << "NULL == (void *)0" << std::endl;
    if (std::is_same<decltype(NULL), std::nullptr_t>::value)
        std::cout << "NULL == nullptr" << std::endl;
    foo(0); // call for foo(int)
    //foo(NULL); // failed compiling
    foo(nullptr); // call for foo(char*)

    char arr_1[10];
    char arr_2[LEN];
    int len = 10;
    const int len_2 = len + 1;
    constexpr int len_2_constexpr = 1 + 2 + 3;
    char arr_3[len_2];
    char arr_4[len_2_constexpr];
    char arr_5[len_foo() + 1];
    char arr_6[len_foo_constexpr() + 1];
    std::cout << fibonacci(10) << std::endl;
    std::cout << fibonacci(10) << std::endl;


    std::cout << "OK" << std::endl;

    return 0;
}

void foo(char *){
    std::cout << "foo(char*) is called" << std::endl;
}

void foo(int){
    std::cout << "foo(int) is called" << std::endl;
}

int len_foo(){
    int i = 2;
    return i;
}

constexpr int len_foo_constexpr(){
    return 5;
}

constexpr int fibonacci(const int n){
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}