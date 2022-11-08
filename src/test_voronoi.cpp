#include <iostream>
#include <string>
#include <algorithm>
#include "voronoi.hpp"

using namespace std;

int PRINT_WIDTH = 30;

void printTitle(string title){
    cout << "--- " << title << " ---" << endl;
}

void printTest(string name, int result){
    int l = name.length();
    int pad = max(PRINT_WIDTH - l, 0);
    cout << name << ": ";
    for(int i = 0; i < pad; i++){ cout << " "; }
    if(result == 0){ cout << "FAILED"; }
    else{ cout << "PASSED"; }
    cout << endl;
}

void testHalfEdgeBasic(){
    printTitle("HalfEdge (basic)");

    HalfEdge * e = new HalfEdge();
    HalfEdge * l = new HalfEdge();
    HalfEdge * r = new HalfEdge();

    // l - e - r - l - e - r - ...
    e->left() = l;
    e->right() = r;
    l->left() = r;
    l->right() = e;
    r->left() = e;
    r->right() = l;
    printTest("assign left", (e->left() == l));
    printTest("assign right", (e->right() == r));
    printTest("assign circle", (l->left()->left()->left() == l));

    delete e;
    delete l;
    delete r;
}

void testBeachlineBasic(){
    printTitle("Beachline (basic)");

    Beachline * list = new Beachline();

}

int main(int, char **)
{
    cout << endl << "    start c++ tests" << endl;
    for(int i = 0; i < PRINT_WIDTH + 8; i++){ cout << "="; }
    cout << endl;

    testHalfEdgeBasic();
    testBeachlineBasic();

    return 0;
}