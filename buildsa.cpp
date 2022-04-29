#include "SuffixArray.hpp"
using namespace std::chrono;

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

    cout << argv[1] << endl;

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

    cout << "pref_len " << pref_len << endl;
    cout << "input " << inputfile << endl;
    cout << "output " << outputfile << endl;

    SuffixArray *sa = new SuffixArray();
    sa->ref = sa->fastaReaderWhole(inputfile);
    sa->construct_sa(inputfile, outputfile, pref_len);
    sa->save();
    
    return 0;
}
