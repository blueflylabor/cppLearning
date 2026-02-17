#include <iostream>
using namespace std;

vector<vector<int>> mat;
template <bool T>
class MagicType
{
    bool magic = T;
};

template <typename T, typename U>
class MagicDualType
{
    T dark;
    U magic;
};

// template<typename T>
// typedef MagicVectorType<vector<T, string>> MVT;

typedef int (*process)(void *);
using NewProcess = int (*)(void *);

template <typename T>
using TrueDarkMagic = MagicDualType<vector<T>, string>;

template <typename... Ts>
class MagicMore;

template <typename Require, typename... Args>
class MagicReqMoreArgs;

template <typename... Args>
void printf(const string &str, Args... args);

template <typename... Ts>
void magic2args(Ts... args)
{
    cout << sizeof...(args) << endl;
}

template <typename T0>
void printf1(T0 val)
{
    cout << val << endl;
}

template <typename T, typename... Ts>
void printf1(T val, Ts... args)
{
    cout << val << endl;
    printf1(args...);
}

template <typename T0, typename... T>
void printf2(T0 t0, T... t)
{
    cout << t0 << endl;
    if constexpr (sizeof...(t) > 0)
        printf2(t...);
}

template <typename T, typename... Ts>
auto printf3(T val, Ts... args)
{
    cout << val << endl;
    (void)initializer_list<T>{([&args]
                               { cout << args << endl; }(), val)...};
}

template <typename... T>
auto sum(T... t)
{
    return (t + ...);
}

template <typename T, typename U>
auto add(T t, U u)
{
    return t + u;
}

template <typename T, int BufSize>
class buffer_t
{
public:
    T &alloc();
    void free(T &item);

private:
    T data[BufSize];
};
buffer_t<int, 100> buf;

template<auto val> void foo(){
    cout << val << endl;
    return ;
}

int main()
{
    vector<MagicType<(1 > 2)>> magic; // not recommend code
    TrueDarkMagic<bool> tdm;
    magic2args();
    magic2args(1);
    magic2args(1, "");

    printf1(1, 2, "123", 1.1);
    printf2(1, 2, "123", 2.2);

    cout << sum(12, 13, 12, 12) << endl;
    cout << add(2, 2.22) << endl;
    
    foo<10>();

    cout << "OK" << endl;
    return 0;
}