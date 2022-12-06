#ifndef h_voronoi
#define h_voronoi

#include <vector>

#include "point.hpp"
#include "edge.hpp"

class Voronoi{

std::vector<Point*> m_target_points;
std::vector<Edge*> m_edges;    

public:
    Voronoi(std::vector<Point*> points);

    void addEdge(Edge* e);

};

#endif