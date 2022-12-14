
#include <math.h>
#include "spdlog/spdlog.h"

#include "fortune.hpp"
#include "arc.hpp"

FortuneAlgorithm::FortuneAlgorithm(Voronoi* diagram){
    spdlog::info("fortune - create Fortune Algorithm");

    m_diagram = diagram;
    const std::vector<Point*>& points = m_diagram->getTargetPoints();

    // create events for all target points
    for (vector<Point*>::const_iterator it = points.begin(); it != points.end(); ++it){
        addEvent(new PointEvent(*it));
    }

    m_beachline = new Beachline();
};

void FortuneAlgorithm::compute(){ 
    spdlog::info("fortune - compute Voronoi Diagram (n_target_points={0})", m_eventQueue.size()); 
    while(processNextEvent()){}; 
    spdlog::info("fortune - computed Voronoi Diagram"); 
    m_diagram->logReport();

};
int FortuneAlgorithm::getEventQueueSize(){ return m_eventQueue.size(); };
void FortuneAlgorithm::addEvent(Event* event){ 
    m_eventQueue.push(event); 
    spdlog::debug("fortune - add {0}", event->asString());
};

bool FortuneAlgorithm::processNextEvent(){
    // check if there are events left
    if (m_eventQueue.empty()){
        spdlog::debug("fortune - empty Event Queue"); 
        return false;
    }

    // get element
    Event* nextEvent = m_eventQueue.top();
    m_eventQueue.pop();

    // update sweepline and handle event
    m_sweeplineY = nextEvent->point()->y();

    spdlog::debug(""); 
    spdlog::debug("fortune - ********* PROCESS NEW EVENT ***********"); 
    spdlog::debug("fortune - ********* BEACHLINE AT y={} ***********", m_sweeplineY); 

    // log
    spdlog::debug("fortune - process {0}", nextEvent->asString()); 

    if (nextEvent->isPointEvent()){
        handlePointEvent((PointEvent*)(nextEvent));
    } else {
        handleCircleEvent((CircleEvent*)(nextEvent));
    }

    // cleanup and return
    delete nextEvent;
    return true;
};

// todo: testing
void FortuneAlgorithm::handleCircleEvent(CircleEvent* event){
    // handle the squeezing of an arc event

    // there are events in the queue that have been invalidated
    if (!event->isValid()){ return; }

    Arc* arc = event->arc();                // arc that is being removed
    spdlog::debug("fortune - handle {0} of {1}", event->asString(), arc->asString()); 

    Arc* left = arc->prev();                // squeezer left
    Arc* right = arc->next();               // squeezer right
    Point* circleCenter = event->point();   // point where arc length is zero

    // handle the diagram edge activity, three edges meet at circleCenter
    Edge* outgoing = new Edge(left->p(), right->p());
    m_diagram->addEdge(outgoing);
    outgoing->setStart(circleCenter);
 
    arc->edge_l()->setEnd(circleCenter);
    arc->edge_r()->setEnd(circleCenter);

    // connect half-edges of left edge
    if(arc->edge_l()->he_right()->p() == arc->p()){
        // right half-edge belongs to same point as arcs target point
        if(arc->edge_r()->he_right()->p() == arc->p()){
            arc->edge_l()->he_right()->left() = arc->edge_r()->he_right();
        } else {
            arc->edge_l()->he_right()->left() = arc->edge_r()->he_left();
        }
    } else {
        if(arc->edge_r()->he_right()->p() == arc->p()){
            arc->edge_l()->he_left()->left() = arc->edge_r()->he_right();
        } else {
            arc->edge_l()->he_left()->left() = arc->edge_r()->he_left();
        }
    }

    // connect half-edges of right edge
    if(arc->edge_r()->he_right()->p() == right->p()){
        // right half-edge belongs to same point as arcs target point
        if(outgoing->he_right()->p() == right->p()){
            arc->edge_r()->he_right()->left() = outgoing->he_right();
        } else {
            arc->edge_r()->he_right()->left() = outgoing->he_left();
        }
    } else {
        if(outgoing->he_right()->p() == right->p()){
            arc->edge_r()->he_left()->left() = outgoing->he_right();
        } else {
            arc->edge_r()->he_left()->left() = outgoing->he_left();
        }
    }

    // connect half-edges of new edge
    if(outgoing->he_right()->p() == left->p()){
        // right half-edge belongs to same point as arcs target point
        if(arc->edge_l()->he_right()->p() == left->p()){
            outgoing->he_right()->left() = arc->edge_l()->he_right();
        } else {
            outgoing->he_right()->left() = arc->edge_l()->he_left();
        }
    } else {
        if(arc->edge_l()->he_right()->p() == left->p()){
            outgoing->he_left()->left() = arc->edge_l()->he_right();
        } else {
            outgoing->he_left()->left() = arc->edge_l()->he_left();
        }
    }

    // update and trigger future updates of beachline
    m_beachline->squeezeArc(arc, outgoing);
    checkForCircleEvent(arc->prev());
    checkForCircleEvent(arc->next());
};

void FortuneAlgorithm::handlePointEvent(PointEvent* event){
    spdlog::debug("fortune - handle {0}", event->asString()); 
    spdlog::debug("fortune - insert new Arc");

    // add new point to the beachline
    Point* targetPoint = event->point();
    Arc* arc = new Arc(targetPoint);

    // init beachline if not existing
    if(m_beachline->isEmpty()){
        m_beachline->initBeachline(arc);
        return;
    };

    // insert newly constructed arc to beachline and save it in the vornoi diagram
    Arc* aboveArc = m_beachline->getArcAbove(targetPoint);
    if(aboveArc){
        spdlog::debug("fortune - found arc above {0}", aboveArc->asString());
        aboveArc->invalidateCircleEvent();
        // create new edge and save it in diagram
        Edge* e = new Edge(aboveArc->p(), targetPoint);
        m_diagram->addEdge(e);
        arc->edge_l() = e;
		m_beachline->splitArc(arc, aboveArc);
    } else {
        spdlog::debug("fortune - found no arc above");
        Arc* rightmost = m_beachline->rightmost();
        Edge* e = new Edge(rightmost->p(), targetPoint);
        m_diagram->addEdge(e);
        arc->edge_l() = e;
		m_beachline->insertAfter(arc, rightmost);
    }
    spdlog::debug("fortune - done inserting Arc");

    // check if inserting the new arc squeezed some other arc to non-existence
    // i.e. if an edge has to be drawn
	checkForCircleEvent(arc->prev());
	checkForCircleEvent(arc->next());
    spdlog::debug("fortune - done handling {0}", event->asString()); 
};

// from https://www.geeksforgeeks.org/equation-of-circle-when-three-points-on-the-circle-are-given/
Point* FortuneAlgorithm::findCircleCenter(double x1, double y1, double x2, double y2, double x3, double y3){
    double x12 = x1 - x2;
    double x13 = x1 - x3;
    double y12 = y1 - y2;
    double y13 = y1 - y3;
    double y31 = y3 - y1;
    double y21 = y2 - y1;
    double x31 = x3 - x1;
    double x21 = x2 - x1;
    double sx13 = pow(x1, 2) - pow(x3, 2);
    double sy13 = pow(y1, 2) - pow(y3, 2);
    double sx21 = pow(x2, 2) - pow(x1, 2);
    double sy21 = pow(y2, 2) - pow(y1, 2);

    double f = ((sx13) * (x12)
                + (sy13) * (x12)
                + (sx21) * (x13)
                + (sy21) * (x13))
                / (2 * ((y31) * (x12) - (y21) * (x13)));
    double g = ((sx13) * (y12)
                + (sy13) * (y12)
                + (sx21) * (y13)
                + (sy21) * (y13))
                / (2 * ((x31) * (y12) - (x21) * (y13)));

    double c = -pow(x1, 2) - pow(y1, 2) - 2 * g * x1 - 2 * f * y1;
    double h = -g;
    double k = -f;

    Point* center = new Point(h, k, -1);
    return center;
}

// todo: testing
void FortuneAlgorithm::checkForCircleEvent(Arc* arc){
    // check if an arc is squeezed to death by two other arcs, thus creating an edge   
    if(!arc){ return; }
    spdlog::debug("fortune - check {0} for CicleEvent", arc->asString());
    arc->invalidateCircleEvent();

    // if the arc is clean splitting another one or at the edge, no circle event can happen, as nothing can get squished
    if(!(arc->prev()) || !(arc->next())){
        spdlog::debug("fortune - arc {0} on the edge, no CicleEvent", arc->asString());
        return;    
    }
    if(arc->prev() == arc->next()){ 
        spdlog::debug("fortune - arc {0} clean splitting, no CicleEvent possible", arc->asString());
        return; 
    }

    // span vectors through the three points
    Point* p_prev = arc->prev()->p();
    Point* p = arc->p();
    Point* p_next = arc->next()->p();

    spdlog::debug("fortune - try circle {0}, {1} and {2}", p_prev->asString(), p->asString(), p_next->asString());

    double l1_x = p_next->x() - p_prev->x();
    double l1_y = p_next->y() - p_prev->y();
    double l2_x = p->x() - p_next->x();
    double l2_y = p->y() - p_next->y();

    // don't know what this cases are
    bool allAligned = (l1_x * l2_y - l1_y * l2_x == 0);
    if (allAligned && (p_prev->x() < p_next->x() || p_next->x() < p->x())){ 
        spdlog::debug("fortune - points on a line, no circle");
        return; 
    }

    bool clockwise = (l1_x * l2_y - l1_y * l2_x < 0);
    if (clockwise){ 
        spdlog::debug("fortune - points clockwise, no circle");
        return; }

    // create new circle event
    Point* circleCenter = findCircleCenter(p_prev->x(), p_prev->y(), p->x(), p->y(), p_next->x(), p_next->y());
    double circleRadius = sqrt((p->x() - circleCenter->x())*(p->x() - circleCenter->x()) + (p->y() - circleCenter->y())*(p->y() - circleCenter->y()));

    // todo: down know what this is doing
    if(circleCenter->y() - circleRadius > m_sweeplineY){ 
        spdlog::debug("fortune - circle center not at sweepline, no circle");
        return; };

	addEvent(new CircleEvent(circleCenter, circleRadius, arc));
}