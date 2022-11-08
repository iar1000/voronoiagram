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


CircleEvent::CircleEvent(Edge* e){

};
bool CircleEvent::isPointEvent() { return false; };
bool CircleEvent::isCircleEvent() { return true; };
Point* CircleEvent::point() { return m_point; };
bool CircleEvent::isValid(){ return valid; };
void CircleEvent::invalidate(){ valid = false; };