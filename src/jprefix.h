// header for jprefix.cc
#include <iostream>  /* for std::istream */
#include "jpopts.h" /* for JPrefixOptoins */

int main(int argc, char **argv);
int copy_stream_prefixed (std::istream &in, std::ostream &out, JPrefixOptions opts);

