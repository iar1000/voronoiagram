
#include "fortune.hpp"

FortuneAlgorithm::FortuneAlgorithm(vector<Point*> points){
    // create events for all target points
    for (vector<Point*>::iterator it = points.begin(); it != points.end(); it++){
        addEvent(new PointEvent(*it));
    }
};

int FortuneAlgorithm::getEventQueueSize(){ return m_eventQueue.size(); };
void FortuneAlgorithm::addEvent(Event* event){ m_eventQueue.push(event); };

bool FortuneAlgorithm::processNextEvent(){
    // check if there are events left
    if (m_eventQueue.empty()){
        return false;
    }

    // get element
    Event* nextEvent = m_eventQueue.top();
    m_eventQueue.pop();

    // update sweepline and handle event
    m_sweeplineY = nextEvent->point()->y();
    if (nextEvent->isPointEvent()){
        handlePointEvent(dynamic_cast<PointEvent*>(nextEvent));
    } else {
        handleCircleEvent(dynamic_cast<CircleEvent*>(nextEvent));
    }
    return true;
};

void FortuneAlgorithm::handleCircleEvent(CircleEvent* event){};

void FortuneAlgorithm::handlePointEvent(PointEvent* event){};

