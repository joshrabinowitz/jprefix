// c program to replicate prefix
// first feature is implementation of --text option

#include "jprefix.h"       /* header for this .cc */

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit() */
#include <time.h>      /* for time() */
#include <sys/time.h>  /* for gettimeofday() */
#include <string>      /* for std::string */
#include <iostream>    /* for std::istream, cin, cout */
#include <vector>      /* for std::vector<type> */
#include <fstream>     /* for std::ifstream */
        
#include "jpdateutils.h"   /* header for jpdateutils.cc */
#include "jpstrutils.h"    /* header for jpstrutils.cc */

int
main(int argc, char **argv)
{
    JPrefixOptions opts = parse_options( argc, argv);    
    // parse_options() may exit with error (or without errors, if passed --help-like options).
    // returns opts if successful.

    int bytes = 0;  // count of bytes output
    int num_errors = 0;
    // no files passed; read data from stdin and prefix its lines
    if (opts.filenames.size() == 0) {   
        bytes += copy_stream_prefixed( std::cin, opts );
    } 
    
    // else open the files passed and prefix their lines
    else {
        for (unsigned int i=0; i < opts.filenames.size(); i++) {
            std::ifstream ifs;
            ifs.open( opts.filenames[i].c_str(),  std::fstream::in );
            if (ifs.fail()) {
                std::cerr << "jprefix: can't open file: " << opts.filenames[i] << std::endl;
                num_errors++;
            } else {
                bytes += copy_stream_prefixed( ifs, opts );
            }
        }
    }
    if (opts.verbose) {
        std::cout << "jprefix: printed " << bytes << " bytes to stdout" << std::endl;
    }

    exit( num_errors > 0 ? EXIT_FAILURE : EXIT_SUCCESS );
}

int copy_stream_prefixed (std::istream &in, JPrefixOptions opts) 
{
    std::string line;
    int len = 0;
    while( getline( in, line ) ) {
        // sure, this is 'inefficient'... but usually overwhelmed by I/O speed
        std::vector<std::string> parts;
        if (opts.text.length() > 0) { parts.push_back(opts.text); }
        if (opts.show_hostname) { parts.push_back(opts.hostname); }
        if (opts.show_timestamp) { parts.push_back( get_date_time() ); }
        if (opts.show_utimestamp) { parts.push_back( get_date_utime() ); }
        if (opts.show_elapsed) { parts.push_back( get_time_elapsed() ); }
        std::string prefix = myjoin( " ", parts );
        std::string newline = prefix.length() ? (prefix + " ") : "";
        newline += line + "\n";
        len += newline.length();
        std::cout << newline;
    }
    return len;
}
