#include <string>
#include <iostream>
#include <vector>     /* for vector<type> */

// holds info configuring how JPrefix runs
struct JPrefixOptions {
    std::string text;       // the arbitrary text to add to each line
    std::string hostname;   // hostname of machine
    std::vector<std::string> filenames; // filenames to show

    int show_hostname;      // should we show hostname
    int verbose;            // should we be verbose

    JPrefixOptions() : show_hostname(0) {}; // initialize show_hostname to 0 on construction
};

JPrefixOptions parse_options( int argc, char **argv);

int copy_stream_prefixed (std::istream &in, JPrefixOptions opts);

std::string myjoin( std::string joiner, std::vector<std::string> array );
std::string get_hostname();

