#ifndef h_arc
#define h_arc

#include "point.hpp"
#include "event.hpp"

class Arc{

    Point* m_point;
    CircleEvent* m_circle_event;

    Arc* m_left;
    Arc* m_right;

    public:
        Arc(Point* p);

        Arc* const & prev() const;
        Arc*       & prev();
        Arc* const & next() const;
        Arc*       & next();
        Point* const & p() const;
        Point*       & p();
        bool hasNext();
        double constructingPointY();
        double constructingPointX();

        void invalidateCircleEvent();
};

#endif