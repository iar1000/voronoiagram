#ifndef h_arc
#define h_arc

#include <string>
#include <iomanip>

#include "point.hpp"
#include "edge.hpp"
#include "event.hpp"

class Arc{

    Point* m_point;
    CircleEvent* m_circle_event;

    Arc* m_next_arc;
    Arc* m_prev_arc;

    Edge* m_edge_l;
    Edge* m_edge_r;

    public:
        Arc(Point* p);

        std::string asString();

        Arc* const & prev() const;
        Arc*       & prev();
        Arc* const & next() const;
        Arc*       & next();
        Point* const & p() const;
        Point*       & p();
        Edge* const & edge_l() const;
        Edge*       & edge_l();
        Edge* const & edge_r() const;
        Edge*       & edge_r();
        bool hasNext();
        double constructingPointY();
        double constructingPointX();

        void invalidateCircleEvent();
};

#endif