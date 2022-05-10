#include<iostream>
#include<string>
#include<vector>
using namespace std;

int test_string() {
    string s = "abcdefg";
    s = s.substr(2,3);
    cout<<s<<endl;

    cout<< (65536<<(20-12))<<endl;
    return 0;
}
#pragma pack(2)
struct test_alignment {
    char a;
    char b;
    int c;
};
struct test_alignment2 {
    char a;
    int c;
    char b;
};
int main() {
    cout<<sizeof(test_alignment)<<endl;
    cout<<sizeof(test_alignment2)<<endl;
    vector<int> vec = {1,5,3,24,9};
    
    return 0;
}


template <class T>
class SmartPtr {
private:
    T* ptr;
    int* counter;
public:
    SmartPtr(T* p = nullptr):ptr(p),count(new int(0))
}


class Singleton
{
private:
    /* data */
    Singleton(/* args */);
    ~Singleton();
public:
    static Singleton& getInstance() {
        static Singleton sin;
        retrun sin;
    } 
};
