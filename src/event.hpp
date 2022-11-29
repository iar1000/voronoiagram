#ifndef h_event
#define h_event

#include "point.hpp"
#include "edge.hpp"

class Event {

    Point* m_point;

    public:
        virtual bool isPointEvent();
        virtual bool isCircleEvent();
        virtual Point* point();
};

class PointEvent : public Event {

    Point* m_point;

    public:
        PointEvent(Point* p);

        virtual bool isPointEvent();
        virtual bool isCircleEvent();
        virtual Point* point();
};

class CircleEvent : public Event {

    Point* m_point;
    Edge* m_edge;
    bool m_valid;

    public:
        CircleEvent(Edge* e);

        virtual bool isPointEvent();
        virtual bool isCircleEvent();
        virtual Point* point();

        bool isValid();
        void invalidate();
};

class CompareEvents {
    public:
        bool operator()(Event* e1, Event* e2);
};

#endif