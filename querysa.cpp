#include "SuffixArray.hpp"

int main(int argc, char *argv[]) {

    for (int x = 0; x < argc; x++) {
        cout << argv[x] << " ";
    }

    string serial_input = argv[1];
    string query_input = argv[2];
    string query_mode_str = argv[3];
    bool query_mode;
    string query_output = argv[4];
    
    cout << serial_input << " " << query_input << " " << query_mode << " " << query_output << endl;

    //Naive or SimpleAccel
    if (query_mode_str == "naive") {
        query_mode = false;
    }
    else {
        query_mode = true;
    }

    SuffixArray *sa = new SuffixArray();
    cout << "\n" << serial_input << endl;
    sa->load(serial_input);
    sa->construct_sa(sa->inputfile, "text", sa->k);
    sa->queries = sa->fastaReaderQuery(query_input);
    
    std::ofstream querystream;
    querystream.open(query_output, std::ios::out);

    /*for (map<string, string>::iterator x = sa->queries.begin(); x != sa->queries.end(); x++) {
        cout << x->first << ":" << x->second << endl;
    }
    */
    for (map<string, string>::iterator x = sa->queries.begin(); x != sa->queries.end(); x++) {
        string name = x->first;
        //Add highest non alphanum ASCII symbol before alphabet for low query
        //Add lowest non alphanum ASCII symbol after alphabet for high query
        string low_query = x->second + "@";
        string high_query = x->second + "{";
        int lower = sa->query(low_query, query_mode);
        int upper = sa->query(high_query, query_mode);
        querystream << name << "\t" << (upper - lower) << "\t";
        for (int x = lower; x < upper; x++) {
            if (x == upper - 1)
                querystream << (*(sa->sa))[x];
            else
                querystream << (*(sa->sa))[x] << "\t";
        }
        querystream << "\n";
    }
    querystream.close();

    return 0;
}   
