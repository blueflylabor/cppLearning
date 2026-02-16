#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <tuple>
using namespace std;

void show(const vector<int> v)
{
    for (auto e : v)
        cout << e << " ";
    cout << "\n";
}

class Foo
{
public:
    int value_a;
    int value_b;
    Foo(int a, int b) : value_a(a), value_b(b) {}
};

class InitListFoo
{
public:
    vector<int> v;
    InitListFoo(initializer_list<int> list)
    {
        for (initializer_list<int>::iterator it = list.begin(); it != list.end(); it++)
            v.push_back(*it);
    }

    void foo(initializer_list<int> list)
    {
        for (std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it)
            v.push_back(*it);
    }
};

tuple<int, double, string> f(){
    return make_tuple(1, 2.3, "456");
}

int main()
{
    vector<int> v1 = {1, 2, 3, 4};
    const vector<int>::iterator itr1 = find(v1.begin(), v1.end(), 2);
    if (itr1 != v1.end())
        *itr1 = 3;
    show(v1);

    const vector<int>::iterator itr2 = find(v1.begin(), v1.end(), 3);
    if (itr2 != v1.end())
        *itr2 = 4;

    for (std::vector<int>::iterator element = v1.begin(); element != v1.end(); ++element)
        std::cout << *element << " ";

    int arr[3] = {3, 2, 1};
    Foo foo(1, 2);
    vector<int> v2 = {1, 2, 3, 5, 4};
    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "foo: " << foo.value_a << ", " << foo.value_b << std::endl;
    for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
        std::cout << *it << " ";
    cout << "\n";

    InitListFoo ilf = {1, 2, 3, 5, 4};
    for (vector<int>::iterator it = ilf.v.begin(); it != ilf.v.end(); it++)
        cout << *it << " ";
    cout << endl;
    ilf.foo({6, 6, 6});
    
    for (vector<int>::iterator it = ilf.v.begin(); it != ilf.v.end(); it++)
        cout << *it << " ";
    cout << endl;

    auto [x, y, z] = f();
    cout << x << " " << y << " " << z << endl;

    cout << "OK" << endl;
    return 0;
}