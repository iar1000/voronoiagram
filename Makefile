
.PHONY: clean
.PHONY: test

SRC_DIR = src
_SHARED_LIB = voronoi.so
SHARED_LIB = $(patsubst %,$(SRC_DIR)/%,$(_SHARED_LIB))
_OBJ = voronoi.o
OBJ = $(patsubst %,$(SRC_DIR)/%,$(_OBJ))

CXX=g++

all: $(OBJ)
	$(CXX) -shared $^ -o $(SHARED_LIB)

%.o: %.cpp
	$(CXX) -fPIC -c $< -o $@

test:
	cd test
	python3 -c "from test.test_voronoi import generate_test_data; generate_test_data()"
	pytest test/test_voronoi.py
	cd ..

clean:
	rm -rf test/data __pycache__ */__pycache__ .pytest_cache *.log src/*.so src/*.o