
#include "point.hpp"

Point::Point(double x, double y, int id){
    m_x = x;
    m_y = y;
    m_id = id;
}
double const & Point::x() const { return m_x; }
double       & Point::x()       { return m_x; }
double const & Point::y() const { return m_y; }
double       & Point::y()       { return m_y; }