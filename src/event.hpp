#ifndef h_event
#define h_event

#include "point.hpp"

class Arc;

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

    Point* m_center;
    double m_radius;
    Arc* m_arc;
    bool m_valid;

    public:
        CircleEvent(Point* center, double radius, Arc* arc);

        virtual bool isPointEvent();
        virtual bool isCircleEvent();
        virtual Point* point();

        bool isValid();
        void invalidate();

        Arc* const & arc() const;
        Arc*       & arc();
};

class CompareEvents {
    public:
        bool operator()(Event* e1, Event* e2);
};

#endif