# import the lib directory
import sys
sys.path.append(".")
sys.path.append("../")

import argparse
import os
from os import listdir
from os.path import isfile, join

import logging
from src.logger import setup_logging

# start testing script
from src.Voronoi import Voronoi
from src.Point import Point
from src.Edge import Edge
from lib.voronoi_lib import Point as Point_cpp
from lib.voronoi_lib import Voronoi as Voronoi_cpp
from lib.voronoi_lib import Fortune as Fortune_cpp
from random import randint


def print_title(title):
    print(f"--- {title} ---")


def print_test(name, value: bool):
    l = len(name)
    pad = max(30 - l, 0)
    print(f"{name}: ", end="")
    for _ in range(pad):
        print(" ", end="")
    print("PASSED" if value else "FAILED")


def test_point():
    print_title("Point (basic)")
    x_1 = randint(1, 10)
    y_1 = randint(1, 10)
    p = Point_cpp(x_1, y_1, 0)
    print_test("init", p.x() == x_1 and p.y() == y_1)

    x_2 = randint(1, 10)
    y_2 = randint(1, 10)
    p.x(x_2)
    p.y(y_2)
    print_test("get and set", p.x() == x_2 and p.y() == y_2)


def test_voronoi():
    print_title("Voronoi (basic)")
    points = []
    for i in range(10):
        points.append(Point_cpp(randint(1, 10), randint(1, 10), i))
    v = Voronoi_cpp(points)
    v_points = v.get_target_points()

    correct_init = True
    for i in range(len(points)):
        if points[i].x() != v_points[i].x() or points[i].y() != v_points[i].y():
            correct_init = False
    print_test("init", correct_init)


def test_fortune():
    print_title("Fortune Algorithm")

    points = []
    for i in range(10):
        points.append(Point_cpp(randint(1, 10), randint(1, 10), i))
    voronoi = Voronoi_cpp(points)
    fortune = Fortune_cpp(voronoi)
    print(f"run fortune (n_points={len(points)})...", end=" ")

    fortune.compute()
    edges = voronoi.get_edges()
    print(f"edges={len(edges)}")
    print_test("didn't crash, yey", True)


def run_testcases():
    print_title("Test end-to-end")

    mypath = "test/data"
    all_files = [f for f in listdir(mypath) if isfile(join(mypath, f))]
    input_files = [f for f in all_files if "input" in f]
    input_files.sort()
    for fn in input_files:
        fn_output = fn.replace("input", "output")
        voronoi = Voronoi()
        voronoi.read_points(join(mypath, fn))
        voronoi.compute()
        voronoi_solution = Voronoi()
        voronoi_solution.read_diagram(join(mypath, fn_output))
        print_test(f"case {fn}", voronoi_solution.is_equal(voronoi))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Interface and Integration test')
    parser.add_argument('-v', '--verbose', nargs="?", default='warn', const='info')
    parser.add_argument('-d', '--debug', default=False, action="store_true")
    args = parser.parse_args()
    log_level = "debug" if args.debug else args.verbose
    if (not setup_logging(console_log_output="stdout", console_log_level=log_level, console_log_color=True,
                          logfile_file="voronoi.log", logfile_log_level="debug", logfile_log_color=True,
                          log_line_template="%(color_on)s[%(created)d] [%(levelname)-8s] %(message)s%(color_off)s")):
        raise Exception("Failed to setup logging, aborting.")
    logging.getLogger('matplotlib').setLevel(logging.WARNING)
    os.environ['SPDLOG_LEVEL'] = log_level  # cpp logging

    print()
    print("    run interface test")
    print("=====================================")

    test_point()
    test_voronoi()
    test_fortune()

    print()
    print("    run integration test")
    print("=====================================")
    run_testcases()