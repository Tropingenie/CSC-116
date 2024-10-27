#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif
#include <stdexcept>

/* Remove if already defined */
typedef long long int64; typedef unsigned long long uint64;

/* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on both
 * windows and linux. */
class Stopwatch{
public:
    Stopwatch(){}//trivial default constructor

    void start(){
        start_time = GetTimeMs64();
        started = true;
    }

    void stop(){
        if (!started) throw std::runtime_error("Error: Stopwatch wasn't started before attempting to stop");
        end_time = GetTimeMs64();
        ended = true;
    }

    uint64 elapsed(){
        if (started && ended) return end_time - start_time;
        else if (started) throw std::runtime_error("Error: Stopwatch is still running");
        else throw std::runtime_error("Error: Stopwatch was never used");
    }

private:
    uint64 GetTimeMs64() {
    #ifdef _WIN32
     /* Windows */
     FILETIME ft;
     LARGE_INTEGER li;

     /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
      * to a LARGE_INTEGER structure. */
     GetSystemTimeAsFileTime(&ft);
     li.LowPart = ft.dwLowDateTime;
     li.HighPart = ft.dwHighDateTime;

     auto ret = static_cast<uint64>(li.QuadPart);
     ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
     ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

     return ret;
    #else
     /* Linux */
     struct timeval tv;

     gettimeofday(&tv, NULL);

     uint64 ret = tv.tv_usec;
     /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
     ret /= 1000;

     /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
     ret += (tv.tv_sec * 1000);

     return ret;
    #endif
    }
    uint64 start_time;
    uint64 end_time;
    bool started {false}, ended{false};
};
