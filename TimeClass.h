#ifndef __JJC__TIMECLASS__H__
#define __JJC__TIMECLASS__H__

#include <chrono>
#include <ctime>

typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;

class TimeClass {
public:
    // empty contructor
    TimeClass(void);

    // updates TimePoint to current time
    void updateTime(void);

    // retrieves current time
    TimePoint getTime(void);

    // updates and retrieves the updated time
    TimePoint getTimeUpdate(void);

    // retrieves the time in seconds since last update
    double getElapsedSeconds(void);

    // updates time before getting delta time
    double getElapsedSecondsUpdate(void);

    // get total time in seconds since object was instantiated
    double getTotalElapsedTime(void);

private:
    // this TimePoint gets set once when the object is instantiated
    TimePoint firstTP;

    // this is always given the value of currentTP before currentTP gets updated
    TimePoint lastTP;

    // operations are usually performed on this TimePoint after it gets saved to lastTP
    TimePoint currentTP;

    // used for calculating time in seconds
    std::chrono::duration<double> elapsedSeconds;

};

TimeClass::TimeClass(void) {
    currentTP = std::chrono::system_clock::now();
    firstTP   = currentTP;
    lastTP    = currentTP;
    currentTP = std::chrono::system_clock::now();
}

void TimeClass::updateTime(void) {
    lastTP = currentTP;
    currentTP = std::chrono::system_clock::now();
}

TimePoint TimeClass::getTime(void) {
    return currentTP;
}

TimePoint TimeClass::getTimeUpdate(void) {
    lastTP = currentTP;
    currentTP = std::chrono::system_clock::now();
    return currentTP;
}

double TimeClass::getElapsedSeconds(void) {
    elapsedSeconds = currentTP - lastTP;
    return elapsedSeconds.count();
}

double TimeClass::getElapsedSecondsUpdate(void) {
    lastTP = currentTP;
    currentTP = std::chrono::system_clock::now();
    elapsedSeconds = currentTP - lastTP;
    return elapsedSeconds.count();
}

double TimeClass::getTotalElapsedTime(void) {
    elapsedSeconds = currentTP - firstTP;
    return elapsedSeconds.count();
}


#endif // __JJC__TIMECLASS__H__

