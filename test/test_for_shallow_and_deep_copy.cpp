#include <iostream>
using namespace std;

class OBJ
{
};

class Shallow
{
public:
    int *data1;
    int size1;
    int data2;
    Shallow(int *d1, int l1, const int d2)
    {
        data1 = d1;
        size1 = l1;
        data2 = d2;
    }
    ~Shallow()
    {
        delete[] data1;
        cout << "destructor executed." << endl;
    }
    void show() const
    {
        for (int i = 0; i < size1; i++)
            cout << i << " ";
        cout << endl
             << data2 << endl;
    }
};

class Deep
{
public:
    int *data1;
    int size1;
    int data2;
    Deep(int *d1, int l1, const int d2)
    {
        data1 = d1;
        size1 = l1;
        data2 = d2;
    }

    Deep(const Deep& other){
        data1 = other.data1;
        size1 = other.size1;
        data2 = other.data2;
        cout << "Constructor executed.\n";
    }

    ~Deep(){
        // delete[] data1;
        // cout << "Destructor executed.\n";
    }

    void show() const
    {
        for (int i = 0; i < size1; i++)
            cout << i << " ";
        cout << endl
             << data2 << endl;
    }

};

class Modern{
    public:
        vector<int> data1;
        int data2;

        Modern(vector<int>& d1, int d2){
            data1 = d1;
            data2 = d2;
        }

        Modern(vector<int> d1, int d2){
            data1 = d1;
            data2 = d2;
        }

        ~Modern(){
        }

        Modern(Modern& other){
            data1 = other.data1;
            data2 = other.data2;
        }

        void show() const{
            for(auto e : data1)
                cout << e << " ";
            cout << endl;
            cout << data2 << endl;
        }
};

int main()
{
    OBJ o1;
    OBJ o2 = o1; // copy construction
    o2 = o1;     // copy assignment
/***
    int size1 = 3;
    int *arr1 = new int[size1];
    for (int i = 0; i < size1; i++)
        arr1[i] = i;

    Shallow s1(arr1, size1, 300);
    s1.show();

    int size2 = 3;
    int *arr2 = new int[size2];
    for (int i = 0; i < size2; i++)
        arr2[i] = i;
    Deep d1(arr2, size2, 300);
    d1.show();
    Deep d2(d1);
    d2.show();
***/
    Modern m1(vector<int>(3), 3);
    m1.show();
    cout << "OK" << endl;
    return 0;
}