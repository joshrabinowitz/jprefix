// option processing utils for jprefix.cc
#include "jpopts.h"
#include <getopt.h>    /* for getopt_long() */
#include <stdlib.h>    /* for exit() */
#include <stdio.h>     /* for printf */
#include <iostream>    /* for std::istream, cin, cout */

#include "jpstrutils.h" /* for myjoin() */
#include "jposutils.h" /* for get_hostname() */

// this code uses getopt_long() from the standard getopt.h library
//  and is subject to its interface.
//
// returns JPrefixOptions on success, exit(1)'s with error to stderr on error.
JPrefixOptions parse_options( int argc, char **argv) {
    JPrefixOptions opts;    // sets all members to 0
    int keep_going = 1;
    while (keep_going) {
        int option_index = 0;
        static struct option long_options[] = {
            {"text",       required_argument, NULL,  't' },
            {"hostname",   no_argument,       NULL,  'h' },
            {"verbose",    no_argument,       NULL,  'v' },
            {"timestamp",  no_argument,       NULL,  'm' },   // tiMestamp
            {"utimestamp", no_argument,       NULL,  'u' },   // utimestamp
            {"elapsed",    no_argument,       NULL,  'e' },   // elapsed time between lines
            {"suffix",     no_argument,       NULL,  's' },   // show addl data at end, not start
            {"quotes",     no_argument,       NULL,  'q' },   // show original line in quotes
            {0,           0,                  0,  0 }
        };

        int c = getopt_long(argc, argv, "t:hvmuesq", long_options, &option_index);
        // getopt_long() successively returns the option characters from the option elements,
        // keeping state in option_index.
        
        if (c == -1) {   // this signals end of options to parse,
            keep_going = 0;      // so break out of our 'while (1)' loop.
        } else {
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
                case 'e':   // elapsed
                    opts.show_elapsed = 1;
                    break;
                case 's':   // suffix
                    opts.show_suffix = 1;
                    break;
                case 'q':   // quote
                    opts.show_quotes = 1;
                    break;
                case 'h':   //  hostname
                    opts.show_hostname = 1;
                    break;

                case 'v':   //  verbose
                    opts.verbose = 1;
                    break;

                case '?':   // unrecognized option
                    std::cerr << "jprefix: error: unrecognized option" << std::endl;
                    std::cerr << get_usage();
                    exit(1);
                    break;

                default:
                    fprintf(stderr, "jprefix: error: getopt returned character code 0%o (%c) ??\n", c, c);
                    exit(1);
            }
        }
    }

   // all remaining arguments are assumed to be filenames to read from argv
   // 'optind' springs into existence from getopt.h
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
           "    [--suffix] [--quotes] [FILENAME] [FILENAME...]\n" 
           "    prepend text or selected data to each line from named files or STDIN\n"
           "    --text=prepend specifies text to prepend to each line\n"
           "    --hostname shows hostname on each line\n"
           "    --timestamp shows time and date\n"
           "    --utimestamp shows date and time with microseconds\n"
           "    --suffix shows added data at end of line, not start\n"
           "    --quotes shows original line in quotes\n";
}

