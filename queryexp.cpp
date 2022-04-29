#include "SuffixArray.hpp"
using namespace std::chrono;

struct HumanReadable {
    std::uintmax_t size{};
  private: friend
    std::ostream& operator<<(std::ostream& os, HumanReadable hr) {
        int i{};
        double mantissa = hr.size;
        for (; mantissa >= 1024.; mantissa /= 1024., ++i) { }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        //os << mantissa << "BKMGTPE"[i];
        //return i == 0 ? os : os << "B (" << hr.size << ')';
        return i == 0 ? os : os << hr.size;
    }
};

int main(int argc, char *argv[]) {
    //--preftab <k>
    //reference
    //output
    
    for (int x = 0; x < argc; x++) {
        cout << argv[x] << " ";
    }

    string inputfile;
    string outputfile;
    int pref_len = -1;

    //cout << argv[1] << endl;

    //Preftable option selected
    if (strcmp(argv[1], "--preftab") == 0) {
        pref_len = atoi(argv[2]);
        inputfile = argv[3];
        outputfile = argv[4];

    }
    else {
        inputfile = argv[1];
        outputfile = argv[2];
    }

    string queryfile = argv[5];
    string query_mode_str = argv[6];
    bool query_mode;
    string timeout = argv[7];

    if (query_mode_str == "naive") {
        query_mode = false;
    }
    else {
        query_mode = true;
    }

    cout << "pref_len " << pref_len << endl;
    cout << "input " << inputfile << endl;
    cout << "output " << outputfile << endl;

    std::ofstream buildfile;
    buildfile.open("query_times.csv", std::ios_base::app);
    if (pref_len == -1 && query_mode_str != "simpaccel") {
        buildfile << "ref_percent,time,preftab,k,search_type\n";
    }

    std::vector<double> ref_percents = {.2, .4, .6, .8, 1};
    for (int x = 0; x < ref_percents.size(); x++) {
        SuffixArray *sa = new SuffixArray();
        sa->ref = sa->fastaReaderWhole(inputfile);
        sa->ref = (sa->ref).substr(0, (sa->ref).length() * ref_percents[x]);
        sa->construct_sa(inputfile, outputfile, pref_len);
        sa->fastaReaderQuery(queryfile);
        cout << "reflen: " << sa->ref.length() << endl;

        auto start = high_resolution_clock::now();
        
        for (map<string, string>::iterator x = sa->queries.begin(); x != sa->queries.end(); x++) {
            string name = x->first;
            //Add highest non alphanum ASCII symbol before alphabet for low query
            //Add lowest non alphanum ASCII symbol after alphabet for high query
            string low_query = x->second + "@";
            string high_query = x->second + "{";
            int lower = sa->query(low_query, query_mode);
            int upper = sa->query(high_query, query_mode);
            //querystream << name << "\t" << (upper - lower) << "\t";
            //for (int x = lower; x < upper; x++) {
                //if (x == upper - 1)
                    //querystream << (*(sa->sa))[x];
                //else
                    //querystream << (*(sa->sa))[x] << "\t";
            //}
            //querystream << "\n";
        }
        //querystream.close();

        auto end = high_resolution_clock::now();

        

        duration<double, std::milli> diff = end - start;
        buildfile << ref_percents[x] << "," << diff.count() << "," << (sa->k != -1) << "," << sa->k << "," << query_mode_str << "\n";
        sa->save();
        delete sa;
    }
    buildfile.close();

    SuffixArray *sa = new SuffixArray();
    sa->ref = sa->fastaReaderWhole(inputfile);
    sa->construct_sa(inputfile, outputfile, pref_len);
    sa->save();

    return 0;
}
