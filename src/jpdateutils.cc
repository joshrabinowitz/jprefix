// date utils for jprefix.cc

#include "jpdateutils.h"    /* header for this jpdateutils.cc */
#include <stdio.h>     /* for snprintf */
#include <iostream>    /* for std::istream, cin, cout */
#include <iomanip>     /* for setprecision() */
#include <sstream>     /* for std::ostringstream */

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

//  get_time_elapsed(). Returns time duration since last called as a string
//  returns 0 first time called
//  Not thread safe but that's ok because this program doesn't use threads.
const std::string get_time_elapsed() {
    timeval diff = get_time_elapsed_timeval();
    return get_timeval_as_string( diff );
}



// static var that stores when we were _last_ called
static timeval prevTime; // = {0};   // all bits 0
const timeval get_time_elapsed_timeval()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);

    timeval diff;
    int sign = 0;
    if (prevTime.tv_sec == 0) {     // first call to this function
       diff.tv_sec = 0;
       diff.tv_usec = 0;
    } else {
        // not the first call to this function
        sign = timeval_subtract( &diff, &curTime, &prevTime );
    }
    prevTime.tv_sec = curTime.tv_sec;   // set the prevTime
    prevTime.tv_usec = curTime.tv_usec;
    return diff;
}

// from http://stackoverflow.com/questions/1858050/how-do-i-compare-two-timestamps-in-c
/* Subtract the `struct timeval' values X and Y,
    storing the result in RESULT.
    Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{

    //dump_timeval( "before: ", *x);
    //dump_timeval( "after: ", *y);

    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    //std::cout << "Getting diff between " << y->tv_sec << "(sec) and " << x->tv_sec << "(sec)\n";
    /* Compute the time remaining to wait.
    tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    //dump_timeval( "result: ", *result);

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}

// return timeval as a duration of seconds
const std::string get_timeval_as_string (const timeval &t) 
{
    double sum = t.tv_sec + t.tv_usec/1000000.0;
    std::ostringstream str;
    //std::cout << "timeval: " << label << ": sec: " << t.tv_sec << ", usec: " << t.tv_usec << " ( " << std::setprecision(6) << std::showpoint << std::fixed << sum << ")\n";
    str << std::setprecision(6) << std::showpoint << std::fixed << sum;
    return str.str();
}

// for debugging
void dump_timeval( const std::string label, const timeval &t ) {
    double sum = t.tv_sec + t.tv_usec/1000000.0;
    std::cout << "timeval: " << label << ": sec: " << t.tv_sec << ", usec: " << t.tv_usec << " ( " << std::setprecision(6) << std::showpoint << std::fixed << sum << ")\n";
}

