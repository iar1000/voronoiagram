import logging
from lib.voronoi_lib import Point as Point_cpp

logger = logging.getLogger()


class Point:
    """data object wrapper for a cpp 2D Point"""

    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.p = None
        logger.debug(f"created {str(self)}")

    def coordinates(self):
        return self.x, self.y

    def to_cpp(self):
        if not self.p:
            self.p = Point_cpp(self.x, self.y, 0)
        return self.p

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __str__(self):
        return f"Point ({self.x},{self.y})"
