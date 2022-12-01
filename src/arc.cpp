#include "arc.hpp"

Arc::Arc(Point* p){
    m_point = p;
    m_circle_event = 0;
    m_prev_arc = m_next_arc = 0;
    m_edge_l = m_edge_r = 0;
}

Arc* const & Arc::prev() const  { return m_prev_arc; };
Arc*       & Arc::prev()        { return m_prev_arc; };
Arc* const & Arc::next() const { return m_next_arc; };
Arc*       & Arc::next()       { return m_next_arc; };
bool Arc::hasNext(){ return m_next_arc; };
Point* const & Arc::p() const { return m_point; };
Point*       & Arc::p() { return m_point; };
Edge* const & Arc::edge_l() const { return m_edge_l; };
Edge*       & Arc::edge_l() { return m_edge_l; };
Edge* const & Arc::edge_r() const { return m_edge_r; };
Edge*       & Arc::edge_r() { return m_edge_r; };

double Arc::constructingPointY(){ return m_point->y(); };
double Arc::constructingPointX(){ return m_point->x(); };

void Arc::invalidateCircleEvent(){
    if(!m_circle_event){ return; }
    m_circle_event->invalidate();
    m_circle_event = 0;
}