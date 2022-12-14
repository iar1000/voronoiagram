
#include "edge.hpp"
#include "spdlog/spdlog.h"

#include <sstream>


Edge::Edge(Point* left, Point* right){
    m_left_target = left;
    m_right_target = right;
	m_he_right = new HalfEdge(right);
	m_he_left = new HalfEdge(left);
	m_he_right->opposite() = m_he_left;
	m_he_left->opposite() = m_he_right;
	m_start = m_end = 0;
    spdlog::debug("edge - created {0}", asString());
}
std::string Edge::asString(){ 
	std::stringstream ss;
	ss << (m_start ? m_start->asString() : "(0)") << "--" << (m_end ? m_end->asString() : "(0)")
	    << ", tl=" << m_left_target->asString() << ", tr=" << m_right_target->asString();
	return "E(" + ss.str() + ")"; // + m_left_target->asString() + " | " + m_right_target->asString() + ")"; 
};
void Edge::setStart(Point* p){ 
    spdlog::debug("edge - start {0}--(0)", p->asString());
	m_start = p; };
void Edge::setEnd(Point* p){ 
	spdlog::debug("edge - end {0}--{1}", m_start ? m_start->asString() : "(0)", p->asString());
	m_end = p; };

HalfEdge* const & Edge::he_right() const { return m_he_right; };
HalfEdge*       & Edge::he_right() { return m_he_right; };
HalfEdge* const & Edge::he_left() const { return m_he_left; };
HalfEdge*       & Edge::he_left() { return m_he_left; };

Point* const & Edge::leftTarget() const { return m_left_target; };
Point*       & Edge::leftTarget(){ return m_left_target; };
Point* const & Edge::rightTarget() const{ return m_right_target; };
Point*       & Edge::rightTarget(){ return m_right_target; };
Point* const & Edge::startPoint() const{ return m_start; };
Point*       & Edge::startPoint(){ return m_start; };
Point* const & Edge::endPoint() const{ return m_end; };
Point*       & Edge::endPoint(){ return m_end; };