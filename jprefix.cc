// c program to replicate prefix
// first feature is implementation of --text option

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit() and gethostname() */
#include <getopt.h>    /* for getopt_long() */
#include <time.h>      /* for time() */
#include <sys/time.h>  /* for gettimeofday() */
#include <string>      /* for std::string */
#include <iostream>    /* for std::istream, cin, cout */
#include <vector>      /* for std::vector<type> */
#include <fstream>     /* for std::ifstream */
        
#include "jprefix.h"    /* header for this .cc */

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
        std::vector<std::string> adds;
        if (opts.text.length() > 0) { adds.push_back(opts.text); }
        if (opts.show_hostname) { adds.push_back(opts.hostname); }
        if (opts.show_timestamp) { adds.push_back( get_date_time() ); }
        if (opts.show_utimestamp) { adds.push_back( get_date_utime() ); }
        std::string prefix = myjoin( " ", adds );
        std::string newline = prefix.length() ? (prefix + " ") : "";
        newline += line + "\n";
        len += newline.length();
        std::cout << newline;
    }
    return len;
}

JPrefixOptions parse_options( int argc, char **argv) {
    int c;
    //int digit_optind = 0;   // used invisibly
    
    JPrefixOptions opts;    // sets all members to 0

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"text",       required_argument, NULL,  't' },
            {"hostname",   no_argument,       NULL,  'h' },
            {"verbose",    no_argument,       NULL,  'v' },
            {"timestamp",  no_argument,      NULL,  'm' },   // tiMestamp
            {"utimestamp", no_argument,      NULL,  'u' },   // utimestamp
            {0,           0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "t:hvmu", long_options, &option_index);
        // returns successively each of the option characters from each of the option elements.
        if (c == -1)    // this signals end of options to parse
            break;

        switch (c) {
        case 't':   // text
            if(optarg) {
                opts.text = optarg;
            } else {
                std::cerr << ("jprefix: error: No value parsed for option --text\n") << get_usage();
                exit(EXIT_FAILURE); 
            }
            break;

        case 'm':   // timestamp - m is for the m in timestamp because t is used
            opts.show_timestamp = 1;
            break;
        case 'u':   // utimestamps
            opts.show_utimestamp = 1;
            break;

        case 'h':   //  hostname
            //std::cout << "jprefix: verbose: show_hostname set to on\n";
            opts.show_hostname = 1;
            break;

        case 'v':   //  verbose
            //std::cout << "jprefix: verbose: verbose set to on\n";
            opts.verbose = 1;
            break;

        case '?':
            std::cout << get_usage();
            exit(0);
            break;

        default:
            printf("jprefix: error: getopt returned character code 0%o (%c) ??\n", c, c);
            exit(1);
        }
    }

   if (optind < argc) {
        //printf("non-option ARGV-elements: ");
        while (optind < argc) {
            opts.filenames.push_back( argv[optind++] );
        }
        if (opts.verbose) {
            std::cout << "jprefix: args: " << myjoin(" ", opts.filenames) << std::endl;
        }
    }
    
    opts.hostname = get_hostname();

    return opts;
}

const std::string get_usage() 
{
    return "jprefix [--text='text'] [--hostname] [--timestamp] [--utimestamp]\n"
           "    [FILENAME] [FILENAME...]\n" 
           "    prepend text or selected data to each line from named files or STDIN\n"
           "    --text=prepend specifies text to prepend to each line\n"
           "    --hostname shows hostname on each line\n";
}

const std::string myjoin( std::string joiner, std::vector<std::string> array ) 
{
    std::string str = "";
    for(unsigned int i=0; i<array.size(); i++) {
        //std::cout << "jprefix: verbose: appending " << array[i] << std::endl;
        str += array[i];
        if(i < array.size() - 1) {
            str += joiner;
        }
    }
    return str;
}

const std::string get_hostname() 
{
    char hostname[1024] = {0};  // {0} means all bits set to 0 in whole array
    gethostname( hostname, 1023 );
    //std::cout << "hostname is " << hostname << std::endl;
    return std::string(hostname);
}
// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string get_date_time()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    char time_date[128] = {0};  // extra space, needs 80
    strftime(time_date, 127, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));
    return time_date;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss.uuuuuu
const std::string get_date_utime()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    char time_date[128] = {0};  // extra space, needs 80
    strftime(time_date, 127, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

    char currentTime[200] = {0}; // extra space for sure
    snprintf(currentTime, 199, "%s.%06ld", time_date, long(curTime.tv_usec) );
    return currentTime;
}

