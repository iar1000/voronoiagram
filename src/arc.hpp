#ifndef h_arc
#define h_arc

#include "point.hpp"
#include "edge.hpp"

class CircleEvent;

class Arc{

    Point* m_point;
    CircleEvent* m_circle_event;

    Arc* m_next_arc;
    Arc* m_prev_arc;

    Edge* m_edge_l;
    Edge* m_edge_r;

    public:
        Arc(Point* p);

        Arc* const & prev() const;
        Arc*       & prev();
        Arc* const & next() const;
        Arc*       & next();
        Point* const & p() const;
        Point*       & p();
        Edge* const & edge_l() const;
        Edge*       & edge_l();
        bool hasNext();
        double constructingPointY();
        double constructingPointX();

        void invalidateCircleEvent();
};

#endif