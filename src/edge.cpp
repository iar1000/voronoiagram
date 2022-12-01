
#include "edge.hpp"

Edge::Edge(Point* left, Point* right){
    m_left_target = left;
    m_right_target = right;
	m_he_right = new HalfEdge(right);
	m_he_left = new HalfEdge(left);
	m_he_right->opposite() = m_he_left;
	m_he_left->opposite() = m_he_right;
	m_start = m_end = 0;
}

void Edge::setStart(Point* p){ m_start = p; };
void Edge::setEnd(Point* p){ m_end = p; };

HalfEdge* const & Edge::he_right() const { return m_he_right; };
HalfEdge*       & Edge::he_right() { return m_he_right; };
HalfEdge* const & Edge::he_left() const { return m_he_left; };
HalfEdge*       & Edge::he_left() { return m_he_left; };