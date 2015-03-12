// string utils for jprefix.cc
#include "jpstrutils.h"
#include <unistd.h>     /* for gethostname */

const std::string myjoin( const std::string joiner, const std::vector<std::string> array ) 
{
    std::string str = "";
    if (1) {
        // STL iterator version. 
        for (std::vector<std::string>::const_iterator it = array.begin(); it != array.end(); it++) {
            str += *it;
            std::vector<std::string>::const_iterator next = it;
            if(++next != array.end()) {
                str += joiner;
            }
        }
    } else {
        // simpler use-int-as-iterator version. 6 short lines
        for(unsigned int i=0; i<array.size(); i++) {
            str += array[i];
            if(i < array.size() - 1) {
                str += joiner;
            }
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

