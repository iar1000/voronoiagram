#include "beachline.hpp"

Beachline::Beachline(){
    m_leftmost = m_rightmost = 0;
}

bool Beachline::isEmpty(){ return (m_leftmost == 0) && (m_rightmost == 0); };
void Beachline::initBeachline(Arc* arc){ m_leftmost = m_rightmost = arc; };

void Beachline::insertAfter(Arc* arc, Arc* nextArc){};

Arc* Beachline::getArcAbove(Point* p){

	for (Arc* arc=m_leftmost; arc; arc=arc->next()) {

		if (!arc->hasNext()) {
			if (arc->constructingPointY() == p->y()){ return 0; }; // arc is not above
			return arc;                                            // arc is above
		}
	}

	return 0;
};
