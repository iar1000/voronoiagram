
.PHONY: clean
.PHONY: test

SRC_DIR = src

_TEST_EXEC = run_test
TEST_EXEC = $(patsubst %,$(SRC_DIR)/%,$(_TEST_EXEC))
_SHARED_LIB = fortune.so
SHARED_LIB = $(patsubst %,$(SRC_DIR)/%,$(_SHARED_LIB))

_OBJ = fortune.o voronoi.o test_runner.o event.o point.o beachline.o arc.o edge.o halfedge.o
OBJ = $(patsubst %,$(SRC_DIR)/%,$(_OBJ))
_HEADERS = voronoi.hpp beachline.hpp point.hpp edge.hpp halfedge.hpp
HEADERS = $(patsubst %,$(SRC_DIR)/%,$(_HEADERS))

CXX = g++ 
INCLUDES = -I. -I/opt/homebrew/Cellar/spdlog/1.10.0_1/include -I/opt/homebrew/Cellar/fmt/9.1.0/include
LINKING = -L/opt/homebrew/Cellar/fmt/9.1.0/lib -lfmt
FLAGS = -std=c++11

default: $(OBJ)
	$(CXX) $^ -o $(TEST_EXEC) $(LINKING)
	$(CXX) -shared $^ -o $(SHARED_LIB) $(LINKING)

%.o: %.cpp
	$(CXX) $(FLAGS) $(INCLUDES) $^ -o $@ -c

test:
	make default
	./src/run_test

debug:
	make default
	./src/run_test SPDLOG_LEVEL=debug

blabla:
	cd test
	python3 -c "from test.test_voronoi import generate_test_data; generate_test_data()"
	pytest test/test_voronoi.py
	cd ..

clean:
	rm -rf test/data __pycache__ */__pycache__ .pytest_cache *.log src/*.so src/*.o src/run_test