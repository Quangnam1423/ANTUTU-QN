#ifndef ATMUTEX_H
#define ATMUTEX_H

namespace AntutuLib
{

class ATMutex
{
public:
    ATMutex() = default;
    virtual ~ATMutex() = default;

    ATMutex(const ATMutex&) = delete;
    ATMutex operator = (const ATMutex&) = delete;

    virtual void lock() = 0;
    virtual bool tryLock() = 0;
    virtual void unlock() = 0;
}; // END ATMutex

} // END NAMESPPACE AntutuLib

#endif // END DECLARATION