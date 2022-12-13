# import the lib directory
import sys
sys.path.append(".")
sys.path.append("../")

# start testing script
from lib.voronoi_lib import *
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
    p = Point(x_1, y_1, 0)
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
        points.append(Point(randint(1, 10), randint(1, 10), i))
    v = Voronoi(points)
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
        points.append(Point(randint(1, 10), randint(1, 10), i))
    voronoi = Voronoi(points)
    fortune = Fortune(voronoi)
    print(f"run fortune (n_points={len(points)})...", end=" ")

    fortune.compute()
    edges = voronoi.get_edges()
    print(f"edges={len(edges)}")
    print_test("didn't crash, yey", True)


if __name__ == '__main__':
    print()
    print("    run python integration tests")
    print("=====================================")

    test_point()
    test_voronoi()
    test_fortune()
