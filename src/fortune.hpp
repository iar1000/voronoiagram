#ifndef h_fortune
#define h_fortune

#include <vector>
#include <queue>
#include "point.hpp"
#include "event.hpp"
#include "edge.hpp"
#include "beachline.hpp"
#include "voronoi.hpp"

using namespace std;

class FortuneAlgorithm{

    Voronoi* m_diagram;
    priority_queue<Event*, vector<Event*>, CompareEvents> m_eventQueue;
    Beachline* m_beachline;
    double m_sweeplineY;

    public:
        FortuneAlgorithm(Voronoi* diagram, vector<Point*> points);

        void compute();

        void addEvent(Event* event);
        bool processNextEvent();
	    void handlePointEvent(PointEvent* event);
	    void handleCircleEvent(CircleEvent* event);
	    void checkForCircleEvent(Arc* arc);
	    Point* findCircleCenter(double x1, double y1, double x2, double y2, double x3, double y3);

	    // for testing and debugging
	    int getEventQueueSize();

};

#endif