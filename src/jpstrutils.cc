// string utils for jprefix.cc
#include "jpstrutils.h"

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


