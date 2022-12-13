#include <vector>
#include <sstream>

#include "voronoi.hpp"
#include "spdlog/spdlog.h"

Voronoi::Voronoi(std::vector<Point*> points){ m_target_points = points; }

const std::vector<Point*>& Voronoi::getTargetPoints() const { return m_target_points; }
const std::vector<Edge*>& Voronoi::getEdges() const { return m_edges; };

void Voronoi::addEdge(Edge* e){ 
	m_edges.push_back(e); 
	spdlog::debug("voronoi - add {0} (n_edges={1})", e->asString(), m_edges.size());	
}

void Voronoi::logReport(){
	spdlog::debug("");	
	spdlog::debug("");	
	spdlog::debug("********* VORONOI DIARGRAM REPORT *********");
	spdlog::debug("***** N_TARGET_POINTS= {0}, N_EDGES= {1} *****", m_target_points.size(), m_edges.size());
	spdlog::debug("");	

	spdlog::debug("Target points:");
	std::stringstream ss;	
	for(int i = 9; i >= 0; i--){
		ss.str("");
		ss.clear();
		for(int j = 0; j < 10; j++){
			bool marked = false;
			for(int k = 0; k < m_target_points.size(); k++){
				Point* p = m_target_points.at(k);

				if (p->x() == i && p->y() == j){
					ss << "■ ";
					marked = true;
					break;
				}
			}
			if(!marked){
				ss << "o ";
			}
		}
		spdlog::debug("{0}", ss.str());	
	}

	spdlog::debug("");	
	spdlog::debug("Edges:");	
	for(int i = 0; i < m_edges.size(); i++){
		spdlog::debug("{0}", m_edges.at(i)->asString());
	}
}