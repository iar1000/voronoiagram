#include "beachline.hpp"

#include <cmath>
#include "spdlog/spdlog.h"


Beachline::Beachline(){
    m_leftmost = m_rightmost = 0;
}

bool Beachline::isEmpty(){ return (m_leftmost == 0) && (m_rightmost == 0); };
void Beachline::initBeachline(Arc* arc){ 
    spdlog::debug("beachline - initialize with {0}", arc->asString()); 
    m_leftmost = m_rightmost = arc; 
};

Arc* const & Beachline::rightmost() const { return m_rightmost; };
Arc*       & Beachline::rightmost(){ return m_rightmost; };
Arc* const & Beachline::leftmost() const { return m_leftmost; };
Arc*       & Beachline::leftmost(){ return m_leftmost; };

// todo: needs testing
void Beachline::splitArc(Arc* newArc, Arc* arc)
{
    spdlog::debug("beachline - split {1} by {0}", newArc->asString(), arc->asString()); 
    Arc* duplicate = new Arc(arc->p());
	duplicate->edge_l() = newArc->edge_l(); // duplicate arc will be the extension after new_arc
	insertAfter(duplicate, arc);
	insertAfter(newArc, arc);
	// arc -> new_arc -> duplicate
    spdlog::debug("beachline - end split, new {0}", newArc->asString()); 
}

void Beachline::insertAfter(Arc* newArc, Arc* arc){
    // from:    prev <-> arc <-> next
    // to:      prev <-> arc <-> new_arc <-> next

    // link newArc to next
    if(newArc){ newArc->next() = arc->next(); }
    if(arc->next()){ arc->next()->prev() = newArc; }
    // linke arc to newArc
    if(arc){ arc->next() = newArc; }
    if(newArc){ newArc->prev() = arc; }

	if (arc==m_rightmost) {
		m_rightmost = newArc;
	}
    spdlog::debug("beachline - new insertion {1}", arc->asString(), newArc->asString()); 
};

// todo: needs testing
Arc* Beachline::getArcAbove(Point* p){

    double directrix = p->y();

	for (Arc* arc=m_leftmost; arc; arc=arc->next()) {

		if (!arc->hasNext()) {
			if (arc->constructingPointY() == directrix){ return 0; };   // arc is not above
			return arc;                                                 // arc is above
		}

		// todo: what does this do
		bool left = arc->constructingPointY() > arc->next()->constructingPointY();

		// **** create solution set *****
		// intersect arc->parabola(baselineY) with arc->next->parabola(baselineY)
		double stretch_para_arc = (arc->constructingPointY() - directrix)/2;
		//Point* vertex_para_arc = new Point(arc->constructingPointX(), arc->constructingPointY() - stretch_para_arc);
        double stretch_para_next_arc = (arc->next()->constructingPointY() - directrix)/2;
		//Point* vertex_para_next_arc = new Point(arc->next()->constructingPointX(), arc->next()->constructingPointY() - stretch_para_next_arc);

		double p1_x = arc->constructingPointX();
        double p1_y = arc->constructingPointY();
        double p1_s = stretch_para_arc;
        double p2_x = arc->next()->constructingPointX();
        double p2_y = arc->next()->constructingPointY();
        double p2_s = stretch_para_next_arc;

        Point* intersection;

        // no intersection
        if (p1_s==0 && p2_s==0) { continue; }
        // same stretch factor
        if (p1_s==p2_s) {
            double x = (p1_x+p2_x)/2;
            double y = ((x - p1_x) * (x - p1_x)) / (4 * p1_s ) + (p1_y - stretch_para_arc); // at(x)
            intersection = new Point(x, y, -1);
        }
        // parabola 1 is same height as baseline, only a point
        else if (p1_s==0) {
            double x = p1_x;
            double y = ((x - p2_x) * (x - p2_x)) / (4 * p2_s ) + (p2_y - stretch_para_next_arc); // parabola.at(x)
            intersection = new Point(x, y, -1);
        // parabola 1 is same height as baseline, only a point
        } else if (p2_s==0) {
            double x = p2_x;
            double y = ((x - p1_x) * (x - p1_x)) / (4 * p1_s ) + (p1_y - stretch_para_arc); // at(x)
            intersection = new Point(x, y, -1);
        // two intersection points
        } else {
            double A = p2_s - p1_s;
            double B = 2 * (p1_s * p2_x - p2_s * p1_x);
            double C = p2_s * (p1_x * p1_x + 4 * p1_s * p1_y) - p1_s * (p2_x * p2_x + 4 * p2_s *p2_y);

            double q = B>0
                ? (B+std::sqrt(B*B-4*A*C))/-2
                : (-B+std::sqrt(B*B-4*A*C))/2;

            double x = q/A;
            double y = ((x - p1_x) * (x - p1_x)) / (4 * p1_s ) + (p1_y - stretch_para_arc); // at(x)

            double x2 = C/q;
            double y2 = ((x2 - p1_x) * (x2 - p1_x)) / (4 * p1_s ) + (p1_y - stretch_para_arc); // at(x2)

            // smaller one is left
            if (x > x2){
                double temp_x = x2;
                double temp_y = y2;
                x2 = x;
                y2 = y;
                x = temp_x;
                y = temp_y;
            }

            if(left){ intersection = new Point(x, y, -1); }
            else { intersection = new Point(x2, y2, -1); }
        }
        // **** create solution set *****

        if (p->x() <= intersection->x()){ return arc; }
	}

	return 0;
};

void Beachline::squeezeArc(Arc* to_remove, Edge* new_edge){
    // remove the arc from the beachline, add the new edge instead
    if (!to_remove->prev()){ m_leftmost = to_remove->next(); }
    if (to_remove->next()){ to_remove->next()->edge_l() = new_edge; }
    else { m_rightmost = to_remove->prev(); }

    // remove the link
    if(to_remove->prev()){ to_remove->prev()->next() = to_remove->next(); }
    if(to_remove->next()){ to_remove->next()->prev() = to_remove->prev(); }
};
