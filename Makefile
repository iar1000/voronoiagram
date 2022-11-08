
.PHONY: clean
.PHONY: test

SRC_DIR = src

_TEST_EXEC = run_test
TEST_EXEC = $(patsubst %,$(SRC_DIR)/%,$(_TEST_EXEC))
_SHARED_LIB = fortune.so
SHARED_LIB = $(patsubst %,$(SRC_DIR)/%,$(_SHARED_LIB))

_OBJ = fortune.o voronoi.o test_runner.o event.o
OBJ = $(patsubst %,$(SRC_DIR)/%,$(_OBJ))
_HEADERS = voronoi.hpp beachline.hpp point.hpp edge.hpp halfedge.hpp
HEADERS = $(patsubst %,$(SRC_DIR)/%,$(_HEADERS))

CXX = g++
FLAGS = -c -I.

default: $(OBJ)
	$(CXX) $^ -o $(TEST_EXEC)
	$(CXX) -shared $^ -o $(SHARED_LIB)

%.o: %.cpp
	$(CXX) $^ -o $@ ${FLAGS}

test:
	make default
	./src/run_test

blabla:
	cd test
	python3 -c "from test.test_voronoi import generate_test_data; generate_test_data()"
	pytest test/test_voronoi.py
	cd ..

clean:
	rm -rf test/data __pycache__ */__pycache__ .pytest_cache *.log src/*.so src/*.o