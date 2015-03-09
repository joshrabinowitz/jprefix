#include "jpopts.h"
#include <getopt.h>    /* for getopt_long() */
#include <iostream>    /* for std::istream, cin, cout */

#include "jpstrutils.h" /* for get_hostname() */

// this code uses getopt_long() from the standard getopt.h library
//  and is subject to its interface.
JPrefixOptions parse_options( int argc, char **argv) {
    JPrefixOptions opts;    // sets all members to 0
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"text",       required_argument, NULL,  't' },
            {"hostname",   no_argument,       NULL,  'h' },
            {"verbose",    no_argument,       NULL,  'v' },
            {"timestamp",  no_argument,       NULL,  'm' },   // tiMestamp
            {"utimestamp", no_argument,       NULL,  'u' },   // utimestamp
            {"elapsed",    no_argument,       NULL,  'e' },   // elapsed time between lines
            {0,           0,                  0,  0 }
        };

        int c = getopt_long(argc, argv, "t:hvmu", long_options, &option_index);
        // getopt_long() successively returns the option characters from the option elements.
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
        case 'e':   // elapsed
            opts.show_elapsed = 1;
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

