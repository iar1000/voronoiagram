#include <iostream>
#include "voronoi.hpp"

using namespace std;

void testHalfEdgeBasic(){
    cout << "HalfEdge (basic):" << endl;

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
    cout << "  assign left: " << (e->left() == l) << endl;
    cout << "  assign right: " << (e->right() == r) << endl;
    cout << "  complete circle: " << (l->left()->left()->left() == l) << endl;

    delete e;
    delete l;
    delete r;
}

void testBeachlineBasic(){
    cout << "EdgeList (basic):" << endl;

    Beachline * list = new Beachline();

}

int main(int, char **)
{
    cout << endl << "    start c++ unit-tests ..." << endl <<
                    "-------------------------------" << endl;

    testHalfEdgeBasic();
    testBeachlineBasic();

    return 0;
}