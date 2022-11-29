
#include "halfedge.hpp"

HalfEdge::HalfEdge(Point* p){ m_point = p; }
HalfEdge* const & HalfEdge::left() const { return m_left; }
HalfEdge*       & HalfEdge::left()       { return m_left; }
HalfEdge* const & HalfEdge::right() const { return m_right; }
HalfEdge*       & HalfEdge::right()       { return m_right; }
HalfEdge* const & HalfEdge::opposite() const { return m_opposite; }
HalfEdge*       & HalfEdge::opposite()       { return m_opposite; }
Point* const & HalfEdge::p() const { return m_point; }
Point*       & HalfEdge::p()       { return m_point; }