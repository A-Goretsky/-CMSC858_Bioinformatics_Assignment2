all:
	g++ -std=c++20 -O3 -I ~/include -L ~/lib SuffixArray.cpp -o buildsa -lsdsl -ldivsufsort -ldivsufsort64

preftab:
	./buildsa --preftab 3 ref out

regulat:
	./buildsa ref out
