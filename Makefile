
.PHONY: clean
.PHONY: test

SRC_DIR = src

_FILES = fortune voronoi test_runner event point beachline arc edge halfedge
SOURCE = $(patsubst %,$(SRC_DIR)/%.cpp,$(_FILES))
OBJ = $(patsubst %,$(SRC_DIR)/%.o,$(_FILES))

_TEST_EXEC = run_test
TEST_EXEC = $(patsubst %,$(SRC_DIR)/%,$(_TEST_EXEC))

_LIB = voronoi_lib
LIB = $(patsubst %,$(SRC_DIR)/%,$(_LIB))
LIB_SUFFIX = `python3-config --extension-suffix`
LIB_SOURCE = $(patsubst %,$(LIB).cpp, $(_LIB))


CXX = g++ 
INCLUDES = -I. -I/opt/homebrew/Cellar/spdlog/1.10.0_1/include -I/opt/homebrew/Cellar/fmt/9.1.0/include
INCLUDES_LIB = -shared -fPIC `python3-config --includes` `python3 -m pybind11 --includes`
LINKING = -L/opt/homebrew/Cellar/fmt/9.1.0/lib -lfmt
FLAGS = -std=c++11

default: $(OBJ)
	$(CXX) $^ -o $(TEST_EXEC) $(LINKING)

test:
	make default
	./src/run_test SPDLOG_LEVEL=warn

debug:
	make default
	./src/run_test SPDLOG_LEVEL=debug

shared: $(SOURCE) $(LIB_SOURCE)
	$(CXX) $(FLAGS) $(INCLUDES) $(INCLUDES_LIB) $^ -o $(LIB)$(LIB_SUFFIX) $(LINKING)	

%.o: %.cpp
	$(CXX) $(FLAGS) $(INCLUDES) $^ -o $@ -c

blabla:
	cd test
	python3 -c "from test.test_voronoi import generate_test_data; generate_test_data()"
	pytest test/test_voronoi.py
	cd ..

clean:
	rm -rf test/data __pycache__ */__pycache__ .pytest_cache *.log src/*.so src/*.o src/run_test