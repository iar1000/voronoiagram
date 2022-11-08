
class Point{
    double m_x;
    double m_y;
    int m_id;
};

class Edge{
    int m_direction;
};

class HalfEdge{
    HalfEdge * m_left;    // left neighbour
    HalfEdge * m_right;   // right neighbour
    Point * m_point;      // associated target point
    Edge * m_edge;        // associated full edge

    public:
        HalfEdge * const left() const { return m_left; }
        HalfEdge * left() { return m_left; }
};

class EdgeList{

    HalfEdge * m_leftmost;
    HalfEdge * m_rightmost;

public:
    EdgeList(){
        m_leftmost = new HalfEdge();
        m_rightmost = new HalfEdge();
    }

};