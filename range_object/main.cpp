#include <iostream>
#include <vector>
#include <algorithm>
//#include "main.h"
#include "release.h"

using namespace std;

int main(int argc, char* argv[]) {

    for(auto i : range(0, 12)) {
        cout << i << ' ';
    }
    cout << endl;

    for(auto i : range(12, 0)) {
        cout << i << ' ';
    }
    cout << endl;

    string s = "Hello World";
    for(int i : range(0, s.size())) {
        cout << s[i] << ' ';
    }
    cout << endl;

    for(auto v : range(1, 20, [](int& i){ return i&1; })) {
        cout << v << ' ';
    }
    cout << endl;

}









//
