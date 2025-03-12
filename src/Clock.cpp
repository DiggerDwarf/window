#include <SW/Clock.hpp>


namespace sw
{

Time::Time(long long microseconds) :
    m_microseconds(microseconds)
{
}

Time::Time() :
    m_microseconds(0)
{
}

float Time::asSeconds() const
{
    return static_cast<float>(this->m_microseconds) / 1000000.0;
}

long long Time::asMicroseconds() const
{
    return this->m_microseconds;
}

Time Time::fromSeconds(float seconds)
{
    return Time(static_cast<long long>(seconds * 1000000));
}

Time Time::fromMicroseconds(long long microseconds)
{
    return Time(microseconds);
}

Time Time::operator-(const Time &other) const
{
    return Time(this->m_microseconds - other.m_microseconds);
}

Time Time::operator+(const Time &other) const
{
    return Time(this->m_microseconds + other.m_microseconds);
}

void Time::operator-=(const Time &other)
{
    this->m_microseconds -= other.m_microseconds;
}

void Time::operator+=(const Time &other)
{
    this->m_microseconds += other.m_microseconds;
}

Clock::Clock()
{
    LARGE_INTEGER ticks;
    QueryPerformanceFrequency(&ticks);
    this->frequency = 1000000.0 / ticks.QuadPart;
    QueryPerformanceCounter(&ticks);
    this->m_startTime = Time(ticks.QuadPart * this->frequency);
}

Time Clock::getElapsed()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    return Time(ticks.QuadPart * this->frequency) - this->m_startTime;
}

Time Clock::restart()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    Time newStart = Time(ticks.QuadPart * this->frequency);
    Time out = newStart - this->m_startTime;
    this->m_startTime = newStart;
    return out;
}

}   // namespace sw
