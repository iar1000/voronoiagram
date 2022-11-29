#ifndef h_edge
#define h_edge

#include "halfedge.hpp"

class Edge{

    Point* m_left_target;
	Point* m_right_target;

	HalfEdge* m_he_right;
	HalfEdge* m_he_left;

public:
    Edge(Point* left, Point* right);
};

#endif