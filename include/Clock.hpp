#ifndef __Clock_hpp_INCLUDED
#define __Clock_hpp_INCLUDED

#include <profileapi.h>

class Time
{
private:
    friend class Clock;
    long long m_microseconds;
    Time(long long microseconds);
public:
    Time();
    float asSeconds() const;
    long long asMicroseconds() const;

    static Time fromSeconds(float seconds);
    static Time fromMicroseconds(long long microseconds);

    Time operator-(const Time& other) const;
    Time operator+(const Time& other) const;
};

class Clock
{
private:
    Time m_startTime;
    double frequency;   // In micros / ticks
public:
    Clock();

    Time getElapsed();
    Time restart();
};


#endif // __Clock_hpp_INCLUDED