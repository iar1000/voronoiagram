
#include "edge.hpp"

Edge::Edge(Point* left, Point* right){
    m_left_target = left;
    m_right_target = right;
	m_he_right = new HalfEdge(right);
	m_he_left = new HalfEdge(left);
	m_he_right->opposite() = m_he_left;
	m_he_left->opposite() = m_he_right;
}