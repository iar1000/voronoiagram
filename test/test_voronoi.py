import csv
import json
import os
import logging

from voronoi.voronoi import *

logger = logging.getLogger()

# test sets
base_dir = "test/data"
os.makedirs(base_dir, exist_ok=True)
base_name = "test_targets_"

test_sets = list()
simple_1 = "simple_1", [
    Point(0, 0),
    Point(1, 0),
    Point(0, 1),
    Point(1, 1)]
test_sets.append(simple_1)

simple_2 = "simple_2", [
    Point(0, 0),
    Point(1, 0),
    Point(0, 1),
    Point(1, 1),
    Point(.5, .5)]
test_sets.append(simple_2)

simple_3 = "simple_3", [
    Point(0, 0),
    Point(1, 1)]
test_sets.append(simple_3)


def generate_test_data():
    """generates test data sets and writes it as csv and json"""

    for curr_set in test_sets:
        name = curr_set[0]
        point_dict = {"points": list()}

        with open(os.path.join(base_dir, base_name + name + ".csv"), 'w') as file:
            writer = csv.writer(file, delimiter=',')
            for p in curr_set[1]:
                writer.writerow(p.as_list())
                point_dict["points"].append(p.as_dict())

        # write json
        with open(os.path.join(base_dir, base_name + name + ".json"), 'w') as file:
            json.dump(point_dict, file)


def test_read_target_points():
    """tests reading in the target points of csv and json sources"""

    for curr_set in test_sets:
        name = curr_set[0]
        points_target = curr_set[1]

        path_csv = os.path.join(base_dir, base_name + name + ".csv")
        path_json = os.path.join(base_dir, base_name + name + ".json")
        paths = [path_csv, path_json]

        for path in paths:
            points_read = read_points(path)
            assert len(points_read) == len(points_target), f"set {path}: not all points detected"
            for t in points_target:
                assert t in points_read, f"set {path}: missing {t}"
