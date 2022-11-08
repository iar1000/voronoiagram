#include "event.hpp"

bool Event::isPointEvent() { return false; };
bool Event::isCircleEvent() { return false; };
Point* Event::point() { return 0; };

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