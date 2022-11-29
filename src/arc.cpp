#include "arc.hpp"

Arc::Arc(Point* p){
    m_point = p;
    m_circle_event = 0;
    m_left = m_right = 0;
}

Arc* const & Arc::prev() const  { return m_left; };
Arc*       & Arc::prev()        { return m_left; };
Arc* const & Arc::next() const { return m_right; };
Arc*       & Arc::next()       { return m_right; };
bool Arc::hasNext(){ return m_right; };
Point* const & Arc::p() const { return m_point; };
Point*       & Arc::p() { return m_point; };

double Arc::constructingPointY(){ return m_point->y(); };
double Arc::constructingPointX(){ return m_point->x(); };

void Arc::invalidateCircleEvent(){
    if(!m_circle_event){ return; }
    m_circle_event->invalidate();
    m_circle_event = 0;
}