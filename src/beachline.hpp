#ifndef h_beachline
#define h_beachline

#include "halfedge.hpp"
#include "point.hpp"

class Beachline{

    HalfEdge * m_leftmost;
    HalfEdge * m_rightmost;

public:
    Beachline(){
        m_leftmost = new HalfEdge();
        m_rightmost = new HalfEdge();
        m_leftmost->right() = m_rightmost;
        m_rightmost->left() = m_leftmost;
    }
    void getLeftEdge(const Point * p);
    void insertRight(HalfEdge * he, HalfEdge * le);
    void remove(HalfEdge * he);

};

#endif