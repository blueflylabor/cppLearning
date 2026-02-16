#include <iostream>
using namespace std;

vector<vector<int>> mat;
template<bool T>
class MagicType{
    bool magic = T;
};

template<typename T, typename U>
class MagicDualType{
    T dark;
    U magic;
};

// template<typename T>
// typedef MagicVectorType<vector<T, string>> MVT; 

typedef int (*process)(void *);
using NewProcess = int(*)(void*);

template<typename T>
using TrueDarkMagic = MagicDualType<vector<T>, string>;

int main(){
    vector<MagicType<(1>2)>> magic; // not recommend code
    TrueDarkMagic<bool> tdm;




    cout << "OK" << endl;
    return 0;
}