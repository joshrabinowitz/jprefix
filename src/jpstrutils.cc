// string utils for jprefix.cc
#include "jpstrutils.h"
#include <unistd.h>     /* for gethostname */

const std::string myjoin( const std::string joiner, const std::vector<std::string> array ) 
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
