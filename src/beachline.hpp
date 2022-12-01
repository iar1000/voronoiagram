#ifndef h_beachline
#define h_beachline

#include "arc.hpp"

class Beachline{

    Arc* m_leftmost;
    Arc* m_rightmost;

public:
    Beachline();

    bool isEmpty();
    void initBeachline(Arc* arc);
    void splitArc(Arc* new_arc, Arc* arc);
    void insertAfter(Arc* new_arc, Arc* arc);
    Arc* getArcAbove(Point* p);
    void squeezeArc(Arc* to_remove, Edge* new_edge);

    Arc* const & rightmost() const;
    Arc*       & rightmost();
    Arc* const & leftmost() const;
    Arc*       & leftmost();
};

#endif