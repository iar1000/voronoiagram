#ifndef h_fortune
#define h_fortune

#include <vector>
#include <queue>
#include "point.hpp"
#include "event.hpp"
#include "edge.hpp"

using namespace std;

class FortuneAlgorithm{

    priority_queue<Event*, vector<Event*>, CompareEvents> m_eventQueue;
    double m_sweeplineY;

    public:
        FortuneAlgorithm(vector<Point*> points);

        void compute();

        void addEvent(Event* event);
        bool processNextEvent();
	    void handlePointEvent(PointEvent* event);
	    void handleCircleEvent(CircleEvent* event);
	    void checkForCircleEvent(Edge* edge);

	    // for testing and debugging
	    int getEventQueueSize();

};

#endif