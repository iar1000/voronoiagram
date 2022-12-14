#include <sstream>
#include <iomanip>

#include "point.hpp"

Point::Point(double x, double y, int id){
    m_x = x;
    m_y = y;
    m_id = id;
}
std::string Point::asString(){ 
    std::ostringstream ss1;
    std::ostringstream ss2;
    std::ostringstream ss3;
    ss1 << std::fixed << std::setprecision(2) << m_x;
    ss2 << std::fixed << std::setprecision(2) << m_y;
    ss3 << m_id;
    std::string s = "P(" + ss1.str() + ", " + ss2.str() + ", id=" + ss3.str() + ")";
    return s; 
}
double const & Point::x() const { return m_x; }
double       & Point::x()       { return m_x; }
double const & Point::y() const { return m_y; }
double       & Point::y()       { return m_y; }
int const & Point::id() const { return m_id; }
int       & Point::id()       { return m_id; }