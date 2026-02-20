#include <iostream>
#include <type_traits>
#include <utility>
#include <string>
#include <vector>
std::vector<int> foo(){
    std::vector<int> temp = {1, 2, 3, 4};
    return temp;
}

void ref(std::string& str){
    std::cout << "left : " << std::endl;
}

void ref(std::string&& str){
    std::cout << "right : " << std::endl;
}
/***
void increase(int& v){
    v++;
}

void foo_(){
    double s = 1;
    increase(s);
}
***/

class A{
    public:
        int* p;
        A():p(new int(1)){
            std::cout << "construct : " << p << std::endl;
        }

        A(A& a):p(new int(*a.p)){
            std::cout << "copy : " << p << std::endl;
        }

        A(A&& a):p(a.p){
            a.p = nullptr;
            std::cout << "move : " << p << std::endl;
        }

        ~A(){
            std::cout << "destruct : " << p << std::endl;
            delete p;
        }
};

A return_rval(bool test){
    A a,b;
    if(test)
        return a;
    else
        return b;
}


int main(){
    const char (&left)[6] = "01234";
    const char* p = "01234";
    const char*&& pr = "01234";
    // const char*& pl = "01234";
    static_assert(std::is_same<decltype("01234"), const char(&)[6]>::value, "");

    std::vector<int> v = foo();

    std::string lv1 = "string";
    std::string&& rv1 = std::move(lv1);
    std::cout << rv1 << std::endl;
    const std::string& lv2 = lv1 + lv1;
    std::cout << lv2 << std::endl;
    std::string&& rv2 = lv1 + lv2;
    rv2 += "Test";
    std::cout << rv2 << std::endl;
    ref(rv2);

    const int &b = std::move(1);

    A obj = return_rval(false);
    std::cout << "obj : " << std::endl;
    std::cout << obj.p << " " << *obj.p << std::endl;

    std::string str = "hello cpp.";
    std::vector<std::string> vec;
    vec.push_back(str);
    std::cout << "str : " << str << std::endl;
    vec.push_back(std::move(str));
    std::cout << "str : " << str << std::endl;

    std::cout << "OK" << std::endl;
    return 0;
}