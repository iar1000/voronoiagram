#include "event.hpp"

bool CompareEvents::operator()(Event* e1, Event* e2){
    return e1->point()->y() == e2->point()->y() ? e1->point()->x() > e2->point()->x() : e1->point()->y() < e2->point()->y();
};

bool Event::isPointEvent() { return false; };
bool Event::isCircleEvent() { return false; };
Point* Event::point() { return m_point; };

PointEvent::PointEvent(Point* p){
    m_point = p;
};
bool PointEvent::isPointEvent(){ return true; };
bool PointEvent::isCircleEvent(){ return false; };
Point* PointEvent::point(){ return m_point; };


CircleEvent::CircleEvent(Point* center, double radius, Arc* arc){
    m_center = center;
    m_radius = radius;
    m_arc = arc;
    m_valid = true;
};
bool CircleEvent::isPointEvent() { return false; };
bool CircleEvent::isCircleEvent() { return true; };
Point* CircleEvent::point() { return m_center; };
bool CircleEvent::isValid(){ return m_valid; };
void CircleEvent::invalidate(){ m_valid = false; };