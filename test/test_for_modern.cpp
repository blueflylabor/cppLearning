#include <iostream>
#include <cstring>

using namespace std;

struct Person{
    char name[50];
    int score;
};

void showPerson(const Person* ps){
    if(ps == nullptr){
        cout << "null ptr !" << endl;
        return;
    }
    cout << "name : " << ps->name << " score : " << ps->score << endl;
}

int main(){
    int x = 42;
    int* p1 = &x;
    cout << "value of x : " << x << endl;
    cout << "p1 pointed value : " << *p1 << endl;
    cout << "add of x : " << &x << endl;
    cout << "p1 stored add : " << p1 << endl;

    *p1 = 100;
    cout << "changed value of x : " << x << endl << endl;

    Person* ps = new Person;
    strcpy(ps->name, "Peter Griffin");
    ps->score = 0;
    showPerson(ps);
    delete ps;
    ps = nullptr;
    showPerson(ps);
    cout << endl;

    const int size = 3;
    int* arr = new int[size];
    for(int i = 0; i < size; i++)
        arr[i] = (i + 1) * 10;


    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete[] arr;
    arr = nullptr;

    cout << endl;

    char* str = new char[20];
    strcpy(str, "hello ptr!");
    cout << "str content : " << str << endl;
    cout << "len of str : " << strlen(str) << endl;
    delete[] str;
    str = nullptr;
    std::cout << "OK" << std::endl;
    return 0;
}