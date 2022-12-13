
.PHONY: clean

SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib

_FILES = fortune voronoi test_runner event point beachline arc edge halfedge
SOURCE = $(patsubst %,$(SRC_DIR)/%.cpp,$(_FILES))
OBJ = $(patsubst %,$(SRC_DIR)/%.o,$(_FILES))

_TEST_EXEC = run_test
TEST_EXEC = $(patsubst %,$(TEST_DIR)/%,$(_TEST_EXEC))

_LIB = voronoi_lib
LIB_SUFFIX = `python3-config --extension-suffix`
LIB_SOURCE = $(patsubst %,$(SRC_DIR)/%.cpp, $(_LIB))
LIB_DESTINATION = $(patsubst %,$(LIB_DIR)/%, $(_LIB))

CXX = g++ 
INCLUDES = -I. -I/opt/homebrew/Cellar/spdlog/1.11.0/include -I/opt/homebrew/Cellar/fmt/9.1.0/include
INCLUDES_LIB = -undefined dynamic_lookup `python3-config --ldflags` -shared -fPIC `python3-config --includes` `python3 -m pybind11 --includes`
LINKING = -L/opt/homebrew/Cellar/fmt/9.1.0/lib -lfmt
FLAGS = -std=c++14

default: $(OBJ)
	$(CXX) $^ -o $(TEST_EXEC) $(LINKING)

%.o: %.cpp
	$(CXX) $(FLAGS) $(INCLUDES) $^ -o $@ -c

test:
	make default
	./$(TEST_DIR)/run_test SPDLOG_LEVEL=warn

debug:
	make default
	./src/run_test SPDLOG_LEVEL=debug

shared: $(SOURCE) $(LIB_SOURCE)
	python3 -c 'import platform; print(platform.platform())'
	python3-config --ldflags
	python3 -m pybind11 --includes
	$(CXX) $(FLAGS) $(INCLUDES) $(INCLUDES_LIB) $^ -o $(LIB_DESTINATION)$(LIB_SUFFIX) $(LINKING)
	python3 $(TEST_DIR)/test_runner.py

clean:
	rm -rf __pycache__ */__pycache__ .pytest_cache *.log lib/*.so src/*.o test/run_test