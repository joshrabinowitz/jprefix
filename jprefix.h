#include <string>
#include <iostream>
#include <vector>     /* for vector<type> */

// holds info configuring how JPrefix runs
struct JPrefixOptions {
    std::string text;       // the arbitrary text to add to each line
    std::string hostname;   // hostname of machine
    std::vector<std::string> filenames; // filenames to show

    bool show_hostname;      // should we show hostname
    bool show_timestamp;     // should we show time
    bool show_utimestamp;    // should we show time
    bool show_elapsed;       // should we show elapsed time
    bool verbose;            // should we be verbose

    JPrefixOptions() : show_hostname(0), show_timestamp(0), show_utimestamp(0), show_elapsed(0), verbose(0) {}; // initialize bools to 0 on construction
};

JPrefixOptions parse_options( int argc, char **argv);

int copy_stream_prefixed (std::istream &in, JPrefixOptions opts);

const std::string get_usage();
const std::string myjoin( const std::string joiner, const std::vector<std::string> array );
const std::string get_hostname();
