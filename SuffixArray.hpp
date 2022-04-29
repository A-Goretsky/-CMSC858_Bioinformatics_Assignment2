#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <sdsl/suffix_arrays.hpp>
#include <sstream>
#include <sdsl/construct_sa.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>
#include <chrono>
#include <filesystem>

using namespace sdsl;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::unordered_map;
using std::tuple;

#pragma once

#ifndef SUFFIX_ARRAY_
#define SUFFIX_ARRAY_

class SuffixArray {
    public:
        string inputfile;
        string outputfile;
        int k;
        int_vector<> *sa;
        string ref;
        unordered_map<string, tuple<int, int>> preftable;
        map<string, string> queries;

        SuffixArray();
        ~SuffixArray();
        bool construct_sa(string inputfile, string outputfile, int k);
        int least_common_prefix(string a, string b);
        int query(string query, bool simpleaccel);
        string getSuffix(int index, int k);
        map<string, string> fastaReaderQuery(string filename);
        const string fastaReaderWhole(string filename);
        bool save();
        bool load(string inputname);
};

#endif
