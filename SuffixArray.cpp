#include "SuffixArray.hpp"
#include <sdsl/construct_sa.hpp>
#include <vector>
#include <cereal/archives/binary.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/tuple.hpp>
#include <fstream>
#include <algorithm>

using namespace sdsl;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;
using std::get;
using std::min;

SuffixArray::SuffixArray() {};
SuffixArray::~SuffixArray() {};

int SuffixArray::least_common_prefix(string a, string b) {
    int count = 0;
    for (int x = 0; x < min(a.length(), b.length()); x++) {
        if (a[x] == b[x]) 
            count++;
        else
            break;
    }
    return count;
}

int SuffixArray::query(string query, bool simpleaccel) {
    /*for (int x = 2964210; x < 2964214; x++) {
        cout << (*sa)[x] << " ";
    }
    */

    int left = 0;
    int right = sa->size();
    int center = -1;
    int left_lcp = -1;
    int right_lcp = -1;
    int center_lcp = -1;
    int m_lcp = -1;

    //use preftable if exists
    if (k > -1) {
        try {
            auto tup = preftable[query.substr(0, k)];
            left = get<0>(tup);
            right = get<1>(tup);
        }
        catch (...) {
            return false;
        }
    }

    if (simpleaccel) {
        left_lcp = least_common_prefix(query, ref.substr((*sa)[left]));
        try {
            right_lcp = least_common_prefix(query, ref.substr((*sa)[right]));
        }
        catch (...) {
            right_lcp = 0;
        }
        center = (int) floor((right + left) / 2);
        center_lcp = min(left_lcp, right_lcp);

        //cout << "left: " << left << endl;
        //cout << "right: " << right << endl;
        //cout << "center: " << center << endl;
        //cout << "left_lcp: " << left_lcp << endl;
        //cout << "right_lcp: " << right_lcp << endl;
        //cout << "center_lcp: " << center_lcp << endl;
        //cout << "m_lcp: " << m_lcp << endl;

        //cout << "before while" << endl;
        //cout << "bool out: " << (left < center) << endl;
        while (left < right) {
            //cout << "bool in top: " << (left < center) << endl;
            center = (int) floor((right + left) / 2);
            string SA_C = ref.substr((*sa)[center]);
            m_lcp = least_common_prefix(query, SA_C);
            center_lcp = min(left_lcp, right_lcp);
            //cout << "outside ifs" << endl;
            if (query.substr(center_lcp) < SA_C.substr(center_lcp)) {
                //cout << "first_if" << endl;
                if (center == left + 1) {
                    //cout << "\n\n" << ref.substr((*sa)[center], query.length()) << endl;
                    return center;
                }
                else {
                    left_lcp = m_lcp;
                    right = center;
                }
            }
            else if (query.substr(center_lcp) > SA_C.substr(center_lcp)) {
                //cout << "second if" << endl;

                if (center == right - 1) {
                    //cout << "inner first" << endl;
                    //cout << "\n\n" << ref.substr((*sa)[right], query.length()) << endl;
                    return right;
                }
                else {
                    //cout << "inner else" << endl;
                    //cout << "left: " << left << endl;
                    //cout << "right: " << right << endl;
                    //cout << "center: " << center << endl;
                    //cout << "left_lcp: " << left_lcp << endl;
                    //cout << "right_lcp: " << right_lcp << endl;
                    //cout << "center_lcp: " << center_lcp << endl;
                    //cout << "m_lcp: " << m_lcp << endl;

                    right_lcp = m_lcp;
                    left = center;
                }
                //cout << "outside else" << endl;
            }
            //cout << "outside outer else" << endl;
            //cout << "bool in bottom: " << (left < center) << endl;
        }
        //cout << "outside while loop" << endl;
    }

    else {
        while (left < right) {
            int center = (int) floor((right + left) / 2);
            string SA_C = ref.substr((*sa)[center]);
            if (query < SA_C) {
                if (center == left + 1) {
                    //cout << "\n\n" << ref.substr((*sa)[center], query.length()) << endl;
                    return center;
                }
                else
                    right = center;
            }
            else if (query > SA_C) {
                if (center == right - 1) {
                    //cout << "\n\n" << ref.substr((*sa)[right], query.length()) << endl;
                    return right;
                }
                else
                    left = center;
            }
        }
    }
    return 0;
}

bool SuffixArray::construct_sa(string inputfile, string outfile, int k) {
    this->inputfile = inputfile;
    this->outputfile = outfile;
    this->k = k;

    const std::string& input = ref;

    sa = new int_vector<>(input.length());
    algorithm::calculate_sa(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), *sa );

    //If k exists, build prefix table as well
    if (k > -1) {
        int left = -1;
        string cur = "";
        for (int x = 0; x < sa->size(); x++) {
            string prefix = ref.substr((*sa)[x], k);
            if (cur != prefix) {
                preftable[cur] = tuple(left, x);
                cur = prefix;
                left = x;
            }  
        }
    }
    /*
    for (auto x = preftable.begin(); x != preftable.end(); x++) {
        cout << x->first << " " << get<0>(x->second) << " " << get<1>(x->second) << endl;
    }
    */
    return true;
}

//Code modified from: https://rosettacode.org/wiki/FASTA_format#C.2B.2B
map<string, string> SuffixArray::fastaReaderQuery(string filename) {

    map<string, string> output;

    std::ifstream input(filename);
    if(!input.good()){
        std::cerr << "Error opening '" << filename <<"'. Bailing out." << std::endl;
        return output;
    }
 
    std::string line, name, content;

    while( std::getline( input, line ).good() ){
        if( line.empty() || line[0] == '>' ){ // Identifier marker
            if( !name.empty() ){ // Print out what we read from the last entry
                output[name] = content;
                //std::cout << name << " : " << content << std::endl;
                name.clear();
            }
            if( !line.empty() ){
                name = line.substr(1);
            }
            content.clear();
        } else if( !name.empty() ){
            if( line.find(' ') != std::string::npos ){ // Invalid sequence--no spaces allowed
                name.clear();
                content.clear();
            } else {
                //output << content;
                content += line;
            }
        }
    }
    
    if( !name.empty() ){ // Print out what we read from the last entry
        output[name] = content;
        //std::cout << name << " : " << content << std::endl;
    }
    
    return output;
}

//Code modified from: https://rosettacode.org/wiki/FASTA_format#C.2B.2B
const string SuffixArray::fastaReaderWhole(string filename) {
 
    std::ifstream input(filename);
    if(!input.good()){
        std::cerr << "Error opening '" << filename <<"'. Bailing out." << std::endl;
        return "";
    }
 
    std::string line, name, content;
    std::stringstream output;
    while( std::getline( input, line ).good() ){
        if( line.empty() || line[0] == '>' ){ // Identifier marker
            if( !name.empty() ){ // Print out what we read from the last entry
                output << content;
                //std::cout << name << " : " << content << std::endl;
                name.clear();
            }
            if( !line.empty() ){
                name = line.substr(1);
            }
            content.clear();
        } else if( !name.empty() ){
            if( line.find(' ') != std::string::npos ){ // Invalid sequence--no spaces allowed
                name.clear();
                content.clear();
            } else {
                //output << content;
                content += line;
            }
        }
    }
    
    if( !name.empty() ){ // Print out what we read from the last entry
        output << content;
        //std::cout << name << " : " << content << std::endl;
    }
    
    return output.str();
}

bool SuffixArray::save() {
    std::ofstream output;
    output.open(outputfile, std::ios::binary | std::ios::out);
    //sa->serialize(output);
    cereal::BinaryOutputArchive cereal_out(output);
    cereal_out(ref, queries, k, preftable, inputfile);
    output.close();
    return true;
}

bool SuffixArray::load(string inputname) {
    std::ifstream inputf;
    inputf.open(inputname, std::ios::binary | std::ios::in);
    //sa->load(inputf);
    cereal::BinaryInputArchive cereal_in(inputf);
    cereal_in(ref, queries, k, preftable, inputfile);
    inputf.close();
    return true;
}
