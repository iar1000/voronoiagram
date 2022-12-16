#ifndef h_point
#define h_point

#include <string>

class Point{

    double m_x;
    double m_y;
    int m_id;

    public:
        Point(double x, double y, int id);

        std::string asString();
        double const & x() const;
        double       & x();
        double const & y() const;
        double       & y();
        int const    & id() const;
        int          & id();
};

#endif