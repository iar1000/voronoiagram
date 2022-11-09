#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "beachline.hpp"
#include "point.hpp"
#include "edge.hpp"
#include "halfedge.hpp"
#include "voronoi.hpp"
#include "event.hpp"
#include "fortune.hpp"

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

void testEventComparison(){
    printTitle("Event comparison");

    CompareEvents* comparator = new CompareEvents();
    Point* p1 = new Point(69.0, 420.0, 0); Event* e1 = new PointEvent(p1);
    Point* p2 = new Point(70.0, 420.0, 1); Event* e2 = new PointEvent(p2);
    Point* p3 = new Point(70.0, 11.0, 2); Event* e3 = new PointEvent(p3);

    printTest("Compare y1 < y2", (*comparator)(e3, e1));
    printTest("Compare y1 > y2", !((*comparator)(e1, e3)));
    printTest("Compare y1==y2 and x1 > x2", (*comparator)(e2, e1));
    printTest("Compare y1==y2 and x1==x2", !((*comparator)(e1, e1)));

    delete p1;
    delete p2;
    delete p3;
    delete e1;
    delete e2;
    delete e3;
}

void testEventQueueBasic(){
    printTitle("EventQueue (basic)");

    vector<Point*> v;
    v.push_back(new Point(11.0, 11.0, 0));
    v.push_back(new Point(11.0, 11.0, 1));
    v.push_back(new Point(11.0, 11.0, 2));
    FortuneAlgorithm* fortune = new FortuneAlgorithm(v);
    printTest("Initialize queue", fortune->getEventQueueSize() == v.size());

    bool passed = true;
    for(int i = 0; i < v.size(); i++){
        fortune->processNextEvent();
        if(fortune->getEventQueueSize() != v.size() - i - 1){ passed = false; };
    }
    printTest("Process events (dequeing)", passed);
}


int main(int, char **)
{
    cout << endl << "    start c++ tests" << endl;
    for(int i = 0; i < PRINT_WIDTH + 8; i++){ cout << "="; }
    cout << endl;

    testHalfEdgeBasic();
    testPointBasic();
    testEventComparison();
    testEventQueueBasic();

    return 0;
}