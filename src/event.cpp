#include "event.hpp"
#include "spdlog/spdlog.h"

#include <sstream>
#include <iomanip>

bool CompareEvents::operator()(Event* e1, Event* e2){
    return e1->point()->y() == e2->point()->y() ? e1->point()->x() > e2->point()->x() : e1->point()->y() < e2->point()->y();
};

bool Event::isPointEvent() { return false; };
bool Event::isCircleEvent() { return false; };
Point* Event::point() { return m_point; };
std::string Event::asString(){ return "Event"; };

PointEvent::PointEvent(Point* p){
    spdlog::debug("create PointEvent({0}, {1})", p->x(), p->y());
    m_point = p;
};
bool PointEvent::isPointEvent(){ return true; };
bool PointEvent::isCircleEvent(){ return false; };
Point* PointEvent::point(){ return m_point; };
std::string PointEvent::asString(){ 
    return "PointEvent(" + m_point->asString() + ")"; 
};


CircleEvent::CircleEvent(Point* center, double radius, Arc* arc){
    m_center = center;
    m_radius = radius;
    m_arc = arc;
    m_valid = true;
};
bool CircleEvent::isPointEvent(){ return false; };
bool CircleEvent::isCircleEvent(){ return true; };
Point* CircleEvent::point(){ return m_center; };
std::string CircleEvent::asString(){ 
    std::stringstream ss2;
    ss2 << std::fixed << std::setprecision(2) << m_radius;

    std::stringstream ss;
    ss << "CircleEvent(" << m_center->asString() << ", r=" << ss2.str() << ")";
    return ss.str(); 
};
bool CircleEvent::isValid(){ return m_valid; };
void CircleEvent::invalidate(){ 
    m_valid = false; 
    spdlog::debug("{0} validity={1}", asString(), m_valid);
};
Arc* const & CircleEvent::arc() const{ return m_arc; };
Arc*       & CircleEvent::arc(){ return m_arc; };