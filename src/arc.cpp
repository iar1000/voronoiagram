#include "arc.hpp"
#include "spdlog/spdlog.h"

#include <sstream>

Arc::Arc(Point* p){
    m_point = p;
    m_circle_event = 0;
    m_prev_arc = m_next_arc = 0;
    m_edge_l = m_edge_r = 0;
    spdlog::debug("arc - created {0}", asString());       
}

std::string Arc::asString(){ 
    std::stringstream ss;
    ss << (m_prev_arc!=0 ? "A(" : "(0)--") << (m_prev_arc!=0 ? m_prev_arc->p()->asString():"") << (m_prev_arc!=0 ? ")--" : "");
    ss << "A(" << m_point->asString() << ")";
    ss << (m_next_arc!=0 ? "--A(" : "--(0)") << (m_next_arc!=0 ? m_next_arc->p()->asString():"") << (m_next_arc!=0 ? ")" : "");
    return ss.str(); 
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
Edge*       & Arc::edge_r() { return m_next_arc->edge_l(); };
Edge* const & Arc::edge_r() const { return m_next_arc->edge_l(); };

double Arc::constructingPointY(){ return m_point->y(); };
double Arc::constructingPointX(){ return m_point->x(); };

void Arc::invalidateCircleEvent(){
    spdlog::debug("arc - invalidate CircleEvent of {0} (has_event={1})", asString(), m_circle_event!=0);    
    if(!m_circle_event){ return; }
    m_circle_event->invalidate();
    m_circle_event = 0;
}