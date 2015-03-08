#include <string>
#include <iostream>
#include <vector>     /* for vector<type> */

struct PrefixOptions {
    std::string text;       // the arbitrary text to add to each line
    std::string hostname;   // hostname of machine
    int show_hostname;      // should we show hostname
    std::vector<std::string> filenames;
};

PrefixOptions parse_options( int argc, char **argv);

int copy_stream_prefixed (std::istream &in, PrefixOptions opts);

std::string myjoin( std::string joiner, std::vector<std::string> array );

