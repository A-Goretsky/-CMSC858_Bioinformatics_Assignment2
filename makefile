all:
	g++ -std=c++20 -O3 -I ~/include -L ~/lib SuffixArray.cpp buildsa.cpp -o buildsa -lsdsl -ldivsufsort -ldivsufsort64
	g++ -std=c++20 -O3 -I ~/include -L ~/lib SuffixArray.cpp querysa.cpp -o querysa -lsdsl -ldivsufsort -ldivsufsort64

preftab:
	./buildsa --preftab 3 ref out

regular:
	./buildsa ref out

file:
	./buildsa --preftab 3 ../sample/ecoli.fa serialized_output

compexp:
	g++ -std=c++20 -O3 -I ~/include -L ~/lib SuffixArray.cpp buildexp.cpp -o buildexp -lsdsl -ldivsufsort -ldivsufsort64
	g++ -std=c++20 -O3 -I ~/include -L ~/lib SuffixArray.cpp queryexp.cpp -o queryexp -lsdsl -ldivsufsort -ldivsufsort64
	g++ -std=c++20 -O3 -I ~/include -L ~/lib SuffixArray.cpp custom_queryexp.cpp -o custom_queryexp -lsdsl -ldivsufsort -ldivsufsort64

customtest:
	g++ -std=c++20 -O3 -I ~/include -L ~/lib SuffixArray.cpp custom_queryexp.cpp -o custom_queryexp -lsdsl -ldivsufsort -ldivsufsort64
	./custom_queryexp --preftab 4 ../sample/ecoli.fa serialized_output ../sample/query.fa naive naivetime.csv
	./custom_queryexp --preftab 4 ../sample/ecoli.fa serialized_output ../sample/query.fa simpaccel naivetime.csv

buildex:
	for number in -1 2 4 6 8 10; do \
    	./buildexp --preftab $$number ../sample/ecoli.fa serialized_output; \
	done

queryex:
	for number in -1 2 4 6 8 10; do \
    	./queryexp --preftab $$number ../sample/ecoli.fa serialized_output ../sample/query.fa naive naivetime.csv;\
	done
	for number in -1 2 4 6 8 10; do \
    	./queryexp --preftab $$number ../sample/ecoli.fa serialized_output ../sample/query.fa simpaccel acceltime.csv;\
	done
	
query:
	./querysa serialized_output ../sample/query.fa naive query_output

query_accel:
	./querysa serialized_output ../sample/query.fa simpaccel query_output
