// option processing utils header for jprefix.cc
#include <string>      /* for std::string */
#include <vector>      /* for std::vector<type> */

// holds info configuring how JPrefix runs
struct JPrefixOptions {
    std::string text;       // the arbitrary text to add to each line
    std::string hostname;   // hostname of machine
    std::vector<std::string> filenames; // filenames to show

    bool show_hostname;      // should we show hostname
    bool show_timestamp;     // should we show time with subseconds
    bool show_utimestamp;    // should we show time
    bool show_elapsed;       // should we show elapsed time
    bool show_suffix;        // should we show the added text at the end
    bool show_quotes;        // should we show the original line in quotes?
    bool verbose;            // should we be verbose

    JPrefixOptions() : // initialize bools to 0 on construction
        show_hostname(0), show_timestamp(0), show_utimestamp(0), show_elapsed(0), show_suffix(0), show_quotes(0), verbose(0) {}; 
};

JPrefixOptions parse_options( int argc, char **argv);
const std::string get_usage();

