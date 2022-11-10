#include "arc.hpp"

Arc::Arc(Point* p){
    m_point = p;
    m_left = m_right = 0;
}

Arc* const & Arc::prev() const  { return m_left; };
Arc*       & Arc::prev()        { return m_left; };
Arc* const & Arc::next() const { return m_right; };
Arc*       & Arc::next()       { return m_right; };
bool Arc::hasNext(){ return m_right; };

double Arc::constructingPointY(){ return m_point->y(); };