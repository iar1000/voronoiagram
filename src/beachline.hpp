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
    void insertAfter(Arc* arc, Arc* nextArc);
    Arc* getArcAbove(Point* p);
};

#endif