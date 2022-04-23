#include "SuffixArray.hpp"
#include <sdsl/construct_sa.hpp>
#include <vector>

using namespace sdsl;
using std::vector;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    //--preftab <k>
    //reference
    //output
    //Handle Prefix table construction call
    for (int x = 0; x < argc; x++) {
        cout << argv[x] << " ";
    }

    string inputfile;
    string outputfile;
    int pref_len = -1;

    if (strcmp(argv[1], "--preftab")) {
        pref_len = atoi(argv[2]);
        inputfile = argv[3];
        outputfile = argv[4];

    }
    else {
        inputfile = argv[1];
        inputfile = argv[2];
    }

    int_vector<> *sa;
    const std::string& input = "blablastring";
    sa = new int_vector<>(input.length());
    algorithm::calculate_sa(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), *sa );
    //algorithm::calculate_sa("test","test"->length(),sa);

    cout << sa->size() << endl;
    auto x = sa->begin();
    while (x != sa->end()) {
        cout << *x << " ";
        x++;
    }

}
