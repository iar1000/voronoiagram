# import the lib directory
import sys

sys.path.append(".")
sys.path.append("../")

from typing import List
import csv
import json
import matplotlib.pyplot as plt
import logging
from src.Helpers import *
from src.Point import Point
from src.Edge import Edge
from lib.voronoi_lib import Point as Point_cpp
from lib.voronoi_lib import Voronoi as Voronoi_cpp
from lib.voronoi_lib import Fortune as Fortune_cpp

logger = logging.getLogger()


class Voronoi:

    def __init__(self):
        self.target_points = None
        self.edges = None
        self.boundary = None

    def plot(self, show=True):
        logger.debug(f"plot diagram, show={show}")
        # don't plot empty diagrams
        if not self.target_points:
            return

        fig, ax = plt.subplots()

        plt.style.use('seaborn-whitegrid')
        xs, ys = [], []
        for p in self.target_points:
            x, y = p.coordinates()
            xs.append(x)
            ys.append(y)

        ax.scatter(xs, ys, marker="X")

        # plot edges
        if self.edges:
            for e in self.edges:
                logger.debug(f"plot {e}")
                x1, y1, x2, y2 = e.for_plot()
                plt.plot((x1, x2), (y1, y2), color="black")

        # plot boundary
        if self.boundary:
            for i in range(len(self.boundary)):
                x1, y1 = self.boundary[i]
                x2, y2 = self.boundary[(i + 1) % len(self.boundary)]
                plt.plot((x1, x2), (y1, y2), color="red")
        if show:
            plt.show()

    def compute(self):
        logger.info("start voronoi diagram computation...")
        voronoi_cpp = Voronoi_cpp([p.to_cpp() for p in self.target_points])
        fortune = Fortune_cpp(voronoi_cpp)
        logger.debug("invoke cpp engine")
        fortune.compute()
        all_edges = [Edge(e_cpp) for e_cpp in voronoi_cpp.get_edges()]
        self.edges = [e for e in all_edges if e.nonzero_length()]
        logger.debug(f"received {len(all_edges)} diagram edges, purged {len(all_edges) - len(self.edges)}")

    def bound_edges(self, puffer=2):
        # find bounding box
        min_x, min_y = sys.float_info.max, sys.float_info.max
        max_x, max_y = sys.float_info.min, sys.float_info.min
        for p in self.target_points:
            x, y = p.coordinates()
            if x < min_x:
                min_x = x
            if x > max_x:
                max_x = x
            if y < min_y:
                min_y = y
            if y > max_y:
                max_y = y
        min_x -= puffer
        max_x += puffer
        min_y -= puffer
        max_y += puffer
        self.boundary = [[min_x, min_y],
                         [min_x, max_y],
                         [max_x, max_y],
                         [max_x, min_y]]
        logger.debug(f"boundary set: {self.boundary}")

        # bound all unbound edges
        for e in self.edges:
            unbound = e.get_unbound_start()
            if unbound:
                logger.debug(f"found unbound {e}")
                x, y = unbound.coordinates()
                xn, yn = e.get_normal()
                ln = line((x, y), (x + 100000 * xn, y + 100000 * yn))
                for i in range(len(self.boundary)):
                    lb = line((self.boundary[i][0], self.boundary[i][1]), (self.boundary[(i + 1) % 4][0], self.boundary[(i + 1) % 4][1]))
                    intersect = intersection(ln, lb)
                    if intersect:
                        x, y = intersect
                        e.bound(x, y)

    def read_points(self, filepath: str):
        """reading in target points from csv or json source"""

        logger.info(f"read target points from '{filepath}'...")
        filetype = filepath.split(".")[1]
        points = list()

        # csv reader
        if filetype == "csv":
            with open(filepath, newline='\n') as file:
                reader = csv.reader(file, delimiter=',')
                row_count = 0
                for row in reader:
                    assert len(row) == 2, f"csv parsing error, to many coordinates on row {row_count}: '{row}'"
                    try:
                        x, y = float(row[0]), float(row[1])
                        points.append(Point(x, y))
                    except ValueError:
                        raise TypeError(f"csv parsing error, coordinate type not numerical on row {row_count}: '{row}'")
                    row_count = row_count + 1
        # json reader
        elif filetype == "json":
            with open(filepath, newline='\n') as file:
                data = json.load(file)
                row_count = 0
                for p_dict in data["points"]:
                    x, y = float(p_dict["x"]), float(p_dict["y"])
                    points.append(Point(x, y))
                    row_count = row_count + 1
        else:
            raise TypeError(f"input filetype '{filetype}' not supported, convert to 'csv' or 'json'")

        logger.info(f"collected {len(points)} Points")
        self.target_points = points
