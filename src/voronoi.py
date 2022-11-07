from typing import List
import argparse
import csv
import json

import logging
from logger import setup_logging

# setup logging
if (not setup_logging(console_log_output="stdout", console_log_level="debug", console_log_color=True,
                      logfile_file="voronoi.log", logfile_log_level="debug", logfile_log_color=True,
                      log_line_template="%(color_on)s[%(created)d] [%(levelname)-8s] %(message)s%(color_off)s")):
    raise Exception("Failed to setup logging, aborting.")
logger = logging.getLogger()


class Point:
    """data object for a 2D Point"""

    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y
        logger.debug(f"created {str(self)}")

    def as_list(self):
        return [self.x, self.y]

    def as_dict(self):
        return {"x": self.x, "y": self.y}

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __str__(self):
        return f"Point ({self.x},{self.y})"


def read_points(filepath: str) -> List:
    """reading in target points from csv or json source"""

    logger.info(f"read target points from '{filepath}'")
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
            for p_dict in data["points"]:
                x, y = float(p_dict["x"]), float(p_dict["y"])
                points.append(Point(x, y))
    else:
        raise TypeError(f"input filetype '{filetype}' not supported, convert to 'csv' or 'json'")

    return points


# main application
if __name__ == '__main__':
    # argument parsing and validity checks
    parser = argparse.ArgumentParser(description='Compute the Voronoi diagram of a set of points in the 2D plane')
    parser.add_argument('filepath_in', type=str,
                        help='filepath to the set of input points, allowed types are .csv and .json')
    parser.add_argument('-out', '--filepath-out', type=str,
                        help="filepath to output the diagram to, default is 'voronoi-out.???'")
    args = parser.parse_args()

    # input/ output
    default_filepath_out = "voronoi-out.json"
    filepath_in = args.filepath_in
    filepath_out = args.filepath_out if args.filepath_out else default_filepath_out

    target_points = read_points(filepath_in)
