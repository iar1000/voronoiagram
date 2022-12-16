import logging

from src.Point import Point
from shapely.geometry import Polygon, MultiPoint, Point as Point_shapely

logger = logging.getLogger()


class Entity:
    """represents an entity of the voronoi diagram, defining a region of points closest to target_point"""

    def __init__(self, target_point: Point):
        self.target_point = target_point
        self.border_points = []
        self.polygon = None

    def distance_to_target(self, p: Point_shapely):
        return p.distance(Point_shapely(self.target_point.coordinates()))

    def add_border_point(self, p: Point):
        self.border_points.append(p)

    def compute_polygon(self):
        logger.debug(f"compute polygon of entity {self.target_point.id()}, n_border_points={len(self.border_points)}")
        points = [(p.coordinates()[0], p.coordinates()[1]) for p in self.border_points]
        mp = MultiPoint(points)
        self.polygon = mp.convex_hull

    def plot(self, fig, ax, color="red"):
        """plots the entities to the given subplot"""
        if not self.polygon:
            self.compute_polygon()

        logger.debug(f"plot entity {self.target_point.id()}, polygon={self.polygon}")

        x, y = self.target_point.coordinates()
        ax.plot(x, y, "X", color=color)

        ax.plot(*self.polygon.exterior.xy)
