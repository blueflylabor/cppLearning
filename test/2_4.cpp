#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
auto showTypeInfo(const T& t){
    if constexpr(std::is_integral<T>::value)
        return t + 1;
    else
        return t + 0.001;
}

int main()
{
    cout << showTypeInfo(5) << endl;
    cout << showTypeInfo(3.14) << endl;
    vector<int> v = {1, 2, 3, 5, 4};
    for(auto e : v)
        cout << e << " ";
    cout << endl;
    for(auto& e : v)
        e += 1;
    for(auto e : v)
        cout << e << " ";
    cout << endl;


    cout << "OK" << endl;
    return 0;
}