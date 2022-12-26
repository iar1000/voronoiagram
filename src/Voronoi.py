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
from src.Entity import Entity
from lib.voronoi_lib import Point as Point_cpp
from lib.voronoi_lib import Voronoi as Voronoi_cpp
from lib.voronoi_lib import Fortune as Fortune_cpp
from shapely.geometry import Point as Point_shapely
from shapely import STRtree

logger = logging.getLogger()


class Voronoi:

    def __init__(self):
        self.target_points = None
        self.edges = None
        self.boundary = None
        self.entities = None
        self.rtree = None
        self.rtree_index_map = None

    def plot(self, show=True):
        logger.debug(f"plot diagram, show={show}")
        # don't plot empty diagrams
        if not self.target_points:
            return

        fig, ax = plt.subplots()

        plt.style.use('seaborn-whitegrid')
        for e_id in self.entities:
            self.entities[e_id].plot(fig, ax)

        # plot boundary
        if self.boundary:
            for i in range(len(self.boundary)):
                x1, y1 = self.boundary[i]
                x2, y2 = self.boundary[(i + 1) % len(self.boundary)]
                # ax.plot((x1, x2), (y1, y2), color="red")
        if show:
            plt.show()

    def get_target_entity_by_id(self, target_point_id):
        """returns the shapely.Polygon representing the voronoi entity"""
        logger.debug(f"query entity for target point {target_point_id}")
        if not self.entities:
            return None

        return self.entities[target_point_id]

    def is_equal(self, other):
        """returns boolean value if the set of entities of the other Voronoi diagram is the same"""
        is_equal = True
        for p in self.target_points:
            logger.debug(f"compare entities for target {p.id()}..")
            check_e = other.get_target_entity_by_id(p.id())
            if check_e and check_e.is_equal(self.entities[p.id()]):
                logger.debug(f"different entities for target {p.id()}")
            else:
                logger.debug(f"same entities for target {p.id()}")
                is_equal = False
        return is_equal

    def compute(self, boundary_buffer=1):
        logger.info("start voronoi diagram computation...")
        voronoi_cpp = Voronoi_cpp([p.to_cpp() for p in self.target_points])
        fortune = Fortune_cpp(voronoi_cpp)
        logger.debug("invoke cpp engine")
        fortune.compute()
        all_edges = [Edge(e_cpp) for e_cpp in voronoi_cpp.get_edges()]
        self.edges = [e for e in all_edges if e.nonzero_length()]
        logger.info(f"received {len(all_edges)} diagram edges, purged {len(all_edges) - len(self.edges)}")
        for e in self.edges:
            logger.debug(e)
        self.set_boundary(buffer=boundary_buffer)
        self.bound_edges()
        self.compute_entities()

    def set_boundary(self, buffer):
        """define the bounding box around the target points"""
        logger.info(f"set square boundary with buffer {buffer}")

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
        min_x -= buffer
        max_x += buffer
        min_y -= buffer
        max_y += buffer
        self.boundary = [[min_x, min_y],
                         [min_x, max_y],
                         [max_x, max_y],
                         [max_x, min_y]]
        logger.debug(f"boundary set: {self.boundary}")

    def bound_edges(self):
        """bound all the unboud edges of the returned diagram by the bounding box"""
        logger.info(f"bound edges with boundary {self.boundary}")

        if not self.edges or not self.target_points:
            logger.warning(f"cannot bound edges, targets={self.target_points}, edges={self.edges}")
            return

        # bound all unbound edges
        for e in self.edges:
            unbound = e.get_unbound_start()
            if unbound:
                logger.debug(f"found unbound {e}")
                x, y = unbound.coordinates()
                xn, yn = e.get_normal()
                ln = line((x, y), (x + 100000 * xn, y + 100000 * yn))
                for i in range(len(self.boundary)):
                    lb = line((self.boundary[i][0], self.boundary[i][1]),
                              (self.boundary[(i + 1) % 4][0], self.boundary[(i + 1) % 4][1]))
                    intersect = intersection(ln, lb)
                    if intersect:
                        x, y = intersect
                        e.bound(x, y)

    def compute_entities(self):
        """creates the voronoi entities"""
        logger.info("compute entities")

        # create entities
        entities = dict()
        for p in self.target_points:
            entities[p.id()] = Entity(p)

        # add the outline points to the corresponding entities
        for e in self.edges:
            for ids in e.get_adjacent_target_ids():
                for bp in e.get_endpoints():
                    entities[ids].add_border_point(bp)
        self.entities = entities

        # add border points to the respective entities
        for bp in self.boundary:
            bp_point_shapely = Point_shapely(bp)
            bp_point = Point(bp[0], bp[1])
            min_d = None
            min_e = None
            for e_id in self.entities:
                if not min_d or \
                        self.entities[e_id].distance_to_target(bp_point_shapely) < min_d:
                    min_d = self.entities[e_id].distance_to_target(bp_point_shapely)
                    min_e = self.entities[e_id]
            min_e.add_border_point(bp_point)

        for e_id in self.entities:
            self.entities[e_id].compute_polygon()

    def compute_rtree(self):
        """computes the spatial index of the entities"""
        logger.info("compute rtree")
        if not self.entities:
            return

        # since we don't now if the target points are indexed sequentially,
        # we have to store a map
        self.rtree_index_map = dict()
        entities = list()
        e_counter = 0
        for e_id in self.entities:
            e = self.entities[e_id]
            entities.append(e.get_polygon())
            self.rtree_index_map[e_counter] = e.get_id()
            e_counter += 1

        self.rtree = STRtree(entities)

    def save(self, filepath: str):
        """saves the diagram as json"""
        filetype = filepath.split(".")[1]
        if filetype != "json":
            logger.warning(f"didn't save diagram, incompatible filetype {filetype}")
            return
        logger.info(f"save diagram in '{filepath}'...")

        dictionary = {}
        dictionary["points"] = list()
        dictionary["entities"] = dict()
        for p in self.target_points:
            dictionary["points"].append(p.to_dict())
        for e_id in self.entities:
            dictionary["entities"][str(e_id)] = self.entities[e_id].get_coords_as_list_of_dict()

        with open(filepath, "w") as outfile:
            json.dump(dictionary, outfile, indent=1)

    def read_diagram(self, filepath: str):
        """reading in voronoi diagram from json source"""
        logger.info(f"read voronoi diagram from '{filepath}'...")
        self.target_points = list()
        self.entities = dict()
        with open(filepath, newline='\n') as file:
            data = json.load(file)
            for p_dict in data["points"]:
                x, y, t_id = float(p_dict["x"]), float(p_dict["y"]), int(p_dict["id"])
                self.target_points.append(Point(x, y, t_id))

            for p in self.target_points:
                e = Entity(p)
                boundary = [Point(x["x"], x["y"], -1) for x in data["entities"][str(p.id())]]
                for b in boundary:
                    e.add_border_point(b)
                e.compute_polygon()
                self.entities[p.id()] = e
        self.compute_rtree()

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
                        x, y, t_id = float(row[0]), float(row[1]), int(row[2])
                        points.append(Point(x, y, target_id=t_id))
                    except ValueError:
                        raise TypeError(f"csv parsing error, coordinate type not numerical on row {row_count}: '{row}'")
                    row_count = row_count + 1
        # json reader
        elif filetype == "json":
            with open(filepath, newline='\n') as file:
                data = json.load(file)
                row_count = 0
                for p_dict in data["points"]:
                    x, y, t_id = float(p_dict["x"]), float(p_dict["y"]), int(p_dict["id"])
                    points.append(Point(x, y, t_id))
                    row_count = row_count + 1
        else:
            raise TypeError(f"input filetype '{filetype}' not supported, convert to 'csv' or 'json'")

        logger.info(f"collected {len(points)} Points")
        self.target_points = points
