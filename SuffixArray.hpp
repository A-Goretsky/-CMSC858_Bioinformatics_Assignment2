#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sdsl/suffix_arrays.hpp>

using std::string;

class SuffixArrayBuilder {
    public:
        string inputfile;
        string outputfile;
        int k;
};
