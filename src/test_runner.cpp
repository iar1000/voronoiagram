#include <iostream>
#include <string>
#include <algorithm>

#include "beachline.hpp"
#include "point.hpp"
#include "edge.hpp"
#include "halfedge.hpp"
#include "voronoi.hpp"
#include "event.hpp"

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

void testPointBasic(){
    printTitle("Point (basic)");

    double x1 = 1.0;
    double x2 = 11.0;
    double y1 = 420.0;
    double y2 = 69.0;
    Point* p1 = new Point(x1, y1, 1);
    printTest("Create Point", ((p1->x() == x1) && (p1->y() == y1)));

    p1->x() = x2;
    p1->y() = y2;
    printTest("Update Point", ((p1->x() == x2) && (p1->y() == y2)));

    delete p1;
}

int main(int, char **)
{
    cout << endl << "    start c++ tests" << endl;
    for(int i = 0; i < PRINT_WIDTH + 8; i++){ cout << "="; }
    cout << endl;

    testHalfEdgeBasic();
    testPointBasic();
    //testEventComparison();
    //testBeachlineBasic();

    return 0;
}