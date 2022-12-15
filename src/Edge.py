import logging
from src.Point import Point
from lib.voronoi_lib import Edge as Edge_cpp

logger = logging.getLogger()


class Edge:
    """data object wrapper for a cpp Edge"""

    def __init__(self, e: Edge_cpp):
        self.e = e
        self.left_target = Point(e.left_target().x(), e.left_target().y()) if e.left_target() else None
        self.right_target = Point(e.right_target().x(), e.right_target().y()) if e.right_target() else None
        self.start_point = Point(e.start_point().x(), e.start_point().y()) if e.start_point() else None
        self.end_point = Point(e.end_point().x(), e.end_point().y()) if e.end_point() else None
        logger.debug(f"created {str(self)}")

    def nonzero_length(self):
        if self.start_point and self.end_point:
            return self.start_point != self.end_point
        return True

    def for_plot(self):
        x1, y1 = self.start_point.coordinates()
        x2, y2 = self.end_point.coordinates()
        return x1, y1, x2, y2

    def get_normal(self):
        """computes normal of vector between left and right target"""
        x1, y1 = self.right_target.coordinates()
        x2, y2 = self.left_target.coordinates()
        mx = (x1 + x2) / 2
        my = (y1 + y2) / 2
        if self.start_point:
            x, y = self.start_point.coordinates()
        elif self.end_point:
            x, y = self.end_point.coordinates()
        else:
            logger.warning("no start or endpoint")
        xn, yn = mx - x, my - y
        return xn, yn

    def get_unbound_start(self):
        """returns starting point of the unbound line"""
        if self.start_point and self.end_point:
            return None
        if self.start_point:
            return self.start_point
        else:
            return self.end_point

    def bound(self, x, y):
        """bound the edge by the given point"""
        if self.start_point and self.end_point:
            logger.warning(f"edge was already bound, tried ({x}, {y}) for {str(self)}")
        if self.start_point:
            self.end_point = Point(x, y)
        else:
            self.start_point = Point(x, y)
        logger.debug(f"bound {str(self)}")

    def __str__(self):
        return f"Edge ({str(self.start_point)} <-> {str(self.end_point)}), tl={str(self.left_target)}, tr={str(self.right_target)}"