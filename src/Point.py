import logging
from lib.voronoi_lib import Point as Point_cpp

logger = logging.getLogger()


class Point:
    """data object wrapper for a cpp 2D Point"""

    def __init__(self, x, y, target_id=-1):
        self.x = x
        self.y = y
        self.target_id = -1 if target_id is None else target_id
        self.p = None
        logger.debug(f"created {str(self)}")

    def coordinates(self):
        return self.x, self.y

    def to_cpp(self):
        if not self.p:
            self.p = Point_cpp(self.x, self.y, self.target_id)
        return self.p

    def to_dict(self):
        return {"x": self.x, "y": self.y, "id": self.target_id}

    def id(self):
        return self.target_id

    def __eq__(self, other):
        if self.target_id and other.target_id:
            return self.target_id == other.target_id
        return self.x == other.x and self.y == other.y

    def __str__(self):
        return f"Point ({self.x},{self.y}, id={self.target_id})"
