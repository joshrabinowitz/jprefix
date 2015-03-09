// c program to replicate prefix
// first feature is implementation of --text option

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit() and perhaps gethostname() */
#include <getopt.h>    /* for getopt_long() */
#include <string>       /* for std::string */
#include <iostream>     /* for std::istream, cin, cout */
#include <vector>     /* for std::vector<type> */
#include <fstream>     /* for std::ifstream */
        
#include "jprefix.h"

int
main(int argc, char **argv)
{
    JPrefixOptions opts = parse_options( argc, argv);    // this may exit with error or not, with --help-like options. returns opts if successful
    //std::cout << "text is " << opts.text << std::endl;

    int bytes = 0;
    if (opts.filenames.size() == 0) {
        bytes += copy_stream_prefixed( std::cin, opts );
    } else {
        for (int i=0; i < opts.filenames.size(); i++) {
            std::ifstream ifs;
            ifs.open( opts.filenames[i].c_str(),  std::fstream::in );
            bytes += copy_stream_prefixed( ifs, opts );
        }
    }
    //std::cout << "jprefix: printed " << bytes << " bytes to stdout" << std::endl;

    exit(EXIT_SUCCESS);
}

int copy_stream_prefixed (std::istream &in, JPrefixOptions opts) 
{
    std::string line;
    int len = 0;
    while( getline( in, line ) ) {
        std::vector<std::string> adds;
        if (opts.text.length() > 0) {
            adds.push_back(opts.text);
        }
        if (opts.show_hostname) {
            adds.push_back(opts.hostname);
        }
        std::string prefix = myjoin( " ", adds );
        line = prefix + " " + line + "\n";
        len += line.length();
        std::cout << line;
    }
    return len;
}

JPrefixOptions parse_options( int argc, char **argv) {
    int c;
    //int digit_optind = 0;   // used invisibly
    
    JPrefixOptions opts;    // sets all members to 0

    while (1) {
        //int this_option_optind = optind ? optind : 1;   // where does 'optint' come from
        //int this_option_optind = 1;   
        int option_index = 0;
        static struct option long_options[] = {
            {"text",     required_argument, NULL,  't' },
            {"hostname", no_argument,       NULL,  'h' },
            {"verbose",  no_argument,       NULL,  'v' },
            //{"add",     required_argument, 0,  0 },
            //{"append",  no_argument,       0,  0 },
            //{"delete",  required_argument, 0,  0 },
            //{"verbose", no_argument,       0,  0 },
            //{"create",  required_argument, 0, 'c'},
            //{"file",    required_argument, 0,  0 },
            {0,         0,                 0,  0 }
        };

       c = getopt_long(argc, argv, "thv", // "abc:d:012", // we're not sure what "t" means here, nor "abc:d:012"
                 long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 't':   // text
            if(optarg) {
                //printf("option t with value '%s'\n", optarg);
                opts.text = optarg;
            } else {
                std::cerr << ("jprefix: error: No value parsed for option --text\n");
                exit(1);
            }
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
            std::cout << ( "jprefix: SHOW USAGE\n" );
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

std::string usage() 
{
    return "jprefix [--text='text'] [--hostname] [FILENAME] [FILENAME...]\n" 
           "    prepend text to each line from named files or STDIN\n"
           "    --text=prepend specifies text to prepend to each line\n"
           "    --hostname shows hostname on each line\n";
}

std::string myjoin( std::string joiner, std::vector<std::string> array ) 
{
    std::string str = "";
    for(int i=0; i<array.size(); i++) {
        //std::cout << "jprefix: verbose: appending " << array[i] << std::endl;
        str += array[i];
        if(i < array.size() - 1) {
            str += joiner;
        }
    }
    return str;
}

std::string get_hostname() 
{
    // GET HOSTNAME
    char hostname[1024] = {0};  // {0} means all bits set to 0 in whole array
    gethostname( hostname, 1023 );
    //std::cout << "hostname is " << hostname << std::endl;
    return std::string(hostname);
}
