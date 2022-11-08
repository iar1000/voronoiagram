#ifndef h_halfedge
#define h_halfedge

#include "point.hpp"
#include "edge.hpp"

class HalfEdge{
    HalfEdge * m_left;    // left neighbour
    HalfEdge * m_right;   // right neighbour
    Point * m_point;      // associated target point
    Edge * m_edge;        // associated full edge

    public:
        HalfEdge() {}
        HalfEdge * const & left() const { return m_left; }
        HalfEdge *       & left()       { return m_left; }
        HalfEdge * const & right() const { return m_right; }
        HalfEdge *       & right()       { return m_right; }
};

#endif