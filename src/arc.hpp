#ifndef h_arc
#define h_arc

#include "point.hpp"

class Arc{

    Point* m_point;

    Arc* m_left;
    Arc* m_right;

    public:
        Arc(Point* p);

        Arc* const & prev() const;
        Arc*       & prev();
        Arc* const & next() const;
        Arc*       & next();
        bool hasNext();
        double constructingPointY();
        double constructingPointX();
};

#endif