#include "list.h"
#include <iostream>
#include <assert.h>
#include <random>
using namespace std;

int main() {
    List<int> list;
    for (int i = 1; i <= 10; i ++) list.insertBack(rand() % 10);
    for (auto i : list) {
        cout << i << ' ';
    }
    cout << endl;
    list.sort();

    for (auto i : list) {
        cout << i << ' ';
    }
    cout << endl;
}
