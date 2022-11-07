
class Point{
    double x;
    double y;
    int id;
};

class Edge{
    int direction;
};

class HalfEdge{
    HalfEdge * left;    // left neighbour
    HalfEdge * right;   // right neighbour
    Point * point;      // associated target point
    Edge * edge;        // associated full edge
};

class EdgeList{

    HalfEdge * leftmost;
    HalfEdge * rightmost;

public:
    EdgeList(){
        leftmost = new HalfEdge();
        rightmost = new HalfEdge();
    }

};