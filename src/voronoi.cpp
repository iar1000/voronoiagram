#include <vector>

#include "voronoi.hpp"

Voronoi::Voronoi(std::vector<Point*> points){ m_target_points = points; }

void Voronoi::addEdge(Edge* e){ m_edges.push_back(e); }
