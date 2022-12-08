#ifndef h_halfedge
#define h_halfedge

#include "point.hpp"

class HalfEdge{
    HalfEdge* m_left;    // left neighbour
    HalfEdge* m_right;   // right neighbour
    HalfEdge* m_opposite;// oposite half-edge
    Point* m_point;      // associated target point

    public:
        HalfEdge(Point* p);
        HalfEdge* const & left() const;
        HalfEdge*       & left();
        HalfEdge* const & right() const;
        HalfEdge*       & right();
        HalfEdge* const & opposite() const;
        HalfEdge*       & opposite();
        Point* const & p() const;
        Point*       & p();
};

#endif