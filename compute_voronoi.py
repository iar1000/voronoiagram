# import the lib directory
import sys
import os

sys.path.append(".")
sys.path.append("../")

import argparse
import logging
from src.logger import setup_logging

from src.Voronoi import Voronoi

logger = logging.getLogger()

# main application
if __name__ == '__main__':
    # argument parsing and validity checks
    parser = argparse.ArgumentParser(description='Compute the Voronoi diagram of a set of points in the 2D plane')
    parser.add_argument('filepath_in', type=str,
                        help='filepath to the set of input points, allowed types are .csv and .json')
    parser.add_argument('-out', '--filepath-out', type=str,
                        help="filepath to output the diagram to, default is 'voronoi-out.json'")
    parser.add_argument('-v', '--verbose', nargs="?", default='warn', const='info')
    parser.add_argument('-d', '--debug', default=False, action="store_true")
    args = parser.parse_args()

    # setup logging
    log_level = "debug" if args.debug else args.verbose
    if (not setup_logging(console_log_output="stdout", console_log_level=log_level, console_log_color=True,
                          logfile_file="voronoi.log", logfile_log_level="debug", logfile_log_color=True,
                          log_line_template="%(color_on)s[%(created)d] [%(levelname)-8s] %(message)s%(color_off)s")):
        raise Exception("Failed to setup logging, aborting.")
    logging.getLogger('matplotlib').setLevel(logging.WARNING)
    os.environ['SPDLOG_LEVEL'] = log_level  # cpp logging

    # input/ output
    default_filepath_out = "voronoi-out.json"
    filepath_in = args.filepath_in
    filepath_out = args.filepath_out if args.filepath_out else default_filepath_out

    voronoi = Voronoi()
    voronoi.read_points(filepath_in)
    voronoi.compute()
    voronoi.bound_edges(puffer=1)
    voronoi.plot(show=True)
