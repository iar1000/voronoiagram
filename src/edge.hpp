#ifndef h_edge
#define h_edge

#include "halfedge.hpp"

class Edge{

    Point* m_left_target;
	Point* m_right_target;

	Point* m_start;
	Point* m_end;

	HalfEdge* m_he_right;
	HalfEdge* m_he_left;

public:
    Edge(Point* left, Point* right);
    std::string asString();
    void setStart(Point* p);
    void setEnd(Point* p);
    HalfEdge* const & he_right() const;
    HalfEdge*       & he_right();
    HalfEdge* const & he_left() const;
    HalfEdge*       & he_left();
    Point* const & leftTarget() const;
    Point*       & leftTarget();
    Point* const & rightTarget() const;
    Point*       & rightTarget();
    Point* const & startPoint() const;
    Point*       & startPoint();
    Point* const & endPoint() const;
    Point*       & endPoint();
};

#endif