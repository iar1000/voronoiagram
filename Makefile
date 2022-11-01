
.PHONY: clean
.PHONY: test

test:
	cd test
	python3 -c "from test.test_voronoi import generate_test_data; generate_test_data()"
	pytest test/test_voronoi.py
	cd ..

clean:
	rm -rf test/data __pycache__ */__pycache__ .pytest_cache *.log