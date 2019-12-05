#include <iostream>
# include "array_list.h"

using namespace std;

int main()
{
//    Array_List<int> d;
//    d.insert(d.begin(), 2);
//    d.push_back(2);
//    d.push_back(3);
//    d.push_back(4);
//    d.push_back(5);
//    for(Array_List<int>::iterator it = d.begin(); it != d.end(); it++){
//        cout << *it<<' ';
//    }





    Array_List<int> d;
    d.begin() == d.end();
    *d.begin();
    //d.begin() == d.end();
        for (int i = 0; i < 10; ++i) {
            d.push_back(i);
        }
       const Array_List<int> d3(d);
        d.erase(d.erase(d.begin()));
       // cout<< d[4]<<' ';
        d[4] = 100;
        cerr << *d.begin() << endl;
        cerr << *(d.begin() + 1) << endl;
        cerr << *(d.begin() + 2) << endl;
        cerr << *(d.begin() + 3) << endl;
        auto it = d.end();
        it -= 2;
        for(auto t : d){
            cout << t<<' ';
        }
        cout<<'\n';
        d.insert(d.erase(it), 321);
        //return 0;
        cerr << endl;
        cerr << "!!!!!\n";
        for (auto it = d.begin(); it != d.end(); ++it) {
            cerr << *it << endl;
        }
        cerr << endl;
        Array_List<int> d2;
        d2 = d;
        d.clear();
        for (auto it = d.begin(); it != d.end(); ++it) {
            cerr << *it << endl;
        }
        cerr << endl;
        for (auto it = d2.begin(); it != d2.end(); ++it) {
            cerr << *it << endl;
        }
        cerr << endl;
        for (auto it = d3.begin(); it != d3.end(); ++it) {
            cerr << *it << endl;
        }
        cerr << endl;
        cerr << *(d3.rbegin()) << endl;
        Array_List<int>::const_iterator re = d3.end();
        --re;
        cerr << *re << endl;
        Array_List<int>::const_iterator re2 = d3.end();
        --re2;
        cerr << (re == re2);
        Array_List<int> a;
        cerr << "\n&&&&&&&&&&&\n";
        for (int i = 0; i < 5; ++i) {
            a.push_back(i);
        }
        for (int i = 5; i < 100; ++i) {
            a.push_back(i);
            auto r = a.begin();
            a.erase(a.begin() + 1);
        }
        //1 96 97 98 99
        cerr << endl;
        for (auto i = a.begin(); i != a.end(); ++i) {
            cerr << *i << " ";
        }
        Array_List<int> c;
        c.push_back(6);
        c.push_back(7);
        Array_List<int>::iterator ncon = c.begin();
        Array_List<int>::const_iterator con = c.begin();
        cerr << "!!!!!\n";
        cerr << endl << (con == ncon )<< endl;
        cerr << endl << (ncon == con)<< endl;
        Array_List<int> test;
        cerr << "^^^^^^^^^^\n";
        cerr << (test.begin() == test.end()) << endl;
        cerr << (test.rbegin() == test.rend()) << endl;
        test.push_back(1);
        test.push_back(2);
        test.push_back(3);
        cerr << *(test.end() - 1);
}


