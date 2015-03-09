#include "jpdateutils.h"    /* header for this jpdateutils.cc */
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

//  get_time_elapsed()
const std::string get_time_elapsed() {
    timeval diff = get_time_elapsed_timeval();
    //double time = diff.tv_sec + (diff.tv_usec / 1000000);

    //double ms = diff.tv_sec * 1000 + diff.tv_usec*1000000;

    //char diffstr[200] = {0}; // extra space for sure
    //snprintf(diffstr, 199, "%0.8lfs", ms );
    //return diffstr;
    return get_timeval_as_string( diff );
}
static timeval prevTime; // = {0};   // all bits 0
const timeval get_time_elapsed_timeval()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);

    timeval diff;
    int sign = 0;
    if (prevTime.tv_sec == 0) {
       diff.tv_sec = 0;
       diff.tv_usec = 0;
    } else {
        sign = timeval_subtract( &diff, &curTime, &prevTime );
    }
    prevTime.tv_sec = curTime.tv_sec;
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

void dump_timeval( const std::string label, const timeval &t ) {
    double sum = t.tv_sec + t.tv_usec/1000000.0;
    std::cout << "timeval: " << label << ": sec: " << t.tv_sec << ", usec: " << t.tv_usec << " ( " << std::setprecision(6) << std::showpoint << std::fixed << sum << ")\n";
}

const std::string get_timeval_as_string (const timeval &t) 
{
    double sum = t.tv_sec + t.tv_usec/1000000.0;
    std::ostringstream str;
    //std::cout << "timeval: " << label << ": sec: " << t.tv_sec << ", usec: " << t.tv_usec << " ( " << std::setprecision(6) << std::showpoint << std::fixed << sum << ")\n";
    str << std::setprecision(6) << std::showpoint << std::fixed << sum;
    return str.str();
}
