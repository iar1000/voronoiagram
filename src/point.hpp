#ifndef h_point
#define h_point

class Point{

    double m_x;
    double m_y;
    int m_id;

    public:
        Point(double x, double y, int id);

        double const & x() const;
        double       & x();
        double const & y() const;
        double       & y();
};

#endif