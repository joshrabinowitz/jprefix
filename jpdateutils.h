
const std::string get_date_time();
const std::string get_date_utime();
const std::string get_time_elapsed();
const timeval get_time_elapsed_timeval();

// returns sign, puts result in *result, modified *x and *y
int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y); 
void dump_timeval( const std::string label, const timeval &timeval );
const std::string get_timeval_as_string (const timeval &t);
