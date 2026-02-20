#include <iostream>
class Base
{
public:
    int value1;
    int value2;
    Base()
    {
        value1 = 1;
    }
    Base(int value) : Base()
    {
        value2 = value;
    }
};

class SubClass : public Base{
    public:
        using Base::Base;
};

struct base{
    virtual void foo(int);
};

struct subclass : base{
    virtual void foo(int) override;
    // virtual void foo(float) override; // invalid
};

struct base_{
    virtual void foo() final;
};

struct subclass1 final : base_{

};

// struct subclass2 : subclass1 {
//
//};

// struct subclass3 : base_{
//    void foo();
//};

class Magic{
    public: 
    Magic() = default;
    Magic& operator = (const Magic&) = delete;
    Magic(int magic_num);
};

enum class new_enum : unsigned int {
    val1, val2, val3 = 100, val4 = 10
};

template<typename T>
std::ostream& operator <<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e){
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

int main()
{
    Base b(2);
    std::cout << b.value1 << std::endl;
    std::cout << b.value2 << std::endl;

    SubClass s(3);
    std::cout << s.value1 << " " << s.value2 << std::endl;

    if(new_enum::val3 == new_enum::val4)
        std::cout << "val3 == val4" << std::endl;

    std:: cout << "OK" << std::endl;
}