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
#include "arc.hpp"
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

    Point* p = new Point(69, 420, 0);

    HalfEdge * e = new HalfEdge(p);
    HalfEdge * l = new HalfEdge(p);
    HalfEdge * r = new HalfEdge(p);

    printTest("target point assigned", (e->p() == p) && (l->p() == p));

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

    e->opposite() = l;
    l->opposite() = e;
    printTest("assign opposite", (e->opposite() == l) && (l->opposite() == e));

    delete e;
    delete l;
    delete r;
    delete p;
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

void testEventBasic(){
    printTitle("Event (basic)");

    CompareEvents* comparator = new CompareEvents();
    Point* p1 = new Point(69.0, 420.0, 0); Event* e1 = new PointEvent(p1);
    Point* p2 = new Point(70.0, 420.0, 1); Event* e2 = new PointEvent(p2);
    Point* p3 = new Point(70.0, 11.0, 2); Event* e3 = new PointEvent(p3);

    printTest("Compare y1 < y2", (*comparator)(e3, e1));
    printTest("Compare y1 > y2", !((*comparator)(e1, e3)));
    printTest("Compare y1==y2 and x1 > x2", (*comparator)(e2, e1));
    printTest("Compare y1==y2 and x1==x2", !((*comparator)(e1, e1)));

    Arc* arc = new Arc(p2);
    CircleEvent* event = new CircleEvent(p1, 10, arc);
    bool wasValid = event->isValid();
    event->invalidate();
    printTest("CircleEvent default validity", wasValid);
    printTest("Invalidate CircleEvent", wasValid && !event->isValid());

    delete event;
    delete arc;
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
    Voronoi* voronoi = new Voronoi(v);
    FortuneAlgorithm* fortune = new FortuneAlgorithm(voronoi, v);
    printTest("Initialize queue", fortune->getEventQueueSize() == v.size());

    bool passed = true;
    for(int i = 0; i < v.size(); i++){
        fortune->processNextEvent();
        if(fortune->getEventQueueSize() != v.size() - i - 1){ passed = false; };
    }
    printTest("Process events (dequeing)", passed);

    delete fortune;
    delete voronoi;
}

void testFortuneAlgorithmBasics(){
    printTitle("FortuneAlgorithm (basics)");

    vector<Point*> v;
    Point* p1 = new Point(0.0, 1.0, 0);
    Point* p2 = new Point(11.0, 11.0, 0);
    Point* p3 = new Point(11.0, 11.0, 0);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    Voronoi* voronoi = new Voronoi(v);
    FortuneAlgorithm* fortune = new FortuneAlgorithm(voronoi, v);
    printTest("Initialize queue", fortune->getEventQueueSize() == v.size());

    Point* middle = fortune->findCircleCenter(0, 1, 2, 1, 1, 2);
    printTest("find circle center", middle->x() == 1 && middle->y() == 1);

    delete p1;
    delete p2;
    delete p3;
    delete fortune;
    delete voronoi;
}

void testBeachlineBasic(){
    printTitle("Beachline (basic)");

    Beachline* b = new Beachline();
    printTest("create empty beachline", b->isEmpty());

    Point* p1 = new Point(420.0, 20.0, 0);
    Arc* arc = new Arc(p1);
    b->initBeachline(arc);
    printTest("init beachline", !(b->isEmpty()));
    printTest("  correct left-end", b->leftmost() == arc);
    printTest("  correct right-end", b->rightmost() == arc);

    Point* p2 = new Point(420.0, 20.0, 0);
    Arc* arc2 = new Arc(p2);
    Point* p3 = new Point(420.0, 20.0, 0);
    Arc* arc3 = new Arc(p3);

    b->insertAfter(arc2, arc);
    bool correctInsertion = (b->leftmost() == arc) && (b->rightmost() == arc2)
                                && (arc->next() == arc2);
    printTest("correct insertion V1", correctInsertion);

    b->insertAfter(arc3, arc);
    bool correctInsertion2 = (b->leftmost() == arc) && (b->rightmost() == arc2)
                                && (arc->next() == arc3) && (arc3->next() == arc2);
    printTest("correct insertion V2", correctInsertion2);



    delete b;
    delete p1;
    delete arc;
    delete p2;
    delete arc2;
    delete p3;
    delete arc3;
}

void testArcBasic(){
    printTitle("Arc (basic)");

    Point* p1 = new Point(420.0, 20.0, 0);
    Arc* arc1 = new Arc(p1);
    Point* p2 = new Point(420.0, 20.0, 0);
    Arc* arc2 = new Arc(p2);
    Point* p3 = new Point(420.0, 20.0, 0);
    Arc* arc3 = new Arc(p3);
    printTest("initialization", (arc1->prev() == 0) && (arc1->next() == 0) && (arc1->edge_l() == 0));

    arc2->next() = arc3;
    arc3->next() = arc1;
    arc1->next() = arc2;
    arc2->prev() = arc3;
    arc3->prev() = arc1;
    arc1->prev() = arc2;
    printTest("connectivity forward", arc1->next()->next()->next() == arc1);
    printTest("connectivity backward", arc3->prev()->prev()->prev() == arc3);

    printTest("access constructing point y", arc1->constructingPointY() == p1->y());

    delete p1;
    delete p2;
    delete p3;
    delete arc1;
    delete arc2;
    delete arc3;
}

void testComputation(){

}

int main(int, char **)
{
    cout << endl << "    start c++ tests" << endl;
    for(int i = 0; i < PRINT_WIDTH + 8; i++){ cout << "="; }
    cout << endl;

    testHalfEdgeBasic();
    testPointBasic();
    testEventBasic();
    testEventQueueBasic();
    testFortuneAlgorithmBasics();
    testBeachlineBasic();
    testArcBasic();

    testComputation();

    return 0;
}