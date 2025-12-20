#ifndef ATTHREAD_H
#define ATTHREAD_H

namespace AntutuLib {
class ATThread 
{
public:
    ATThread() = default;
    virtual ~ATThread() = default;

    ATThread(const ATThread&) = delete;
    ATThread& operator = (const ATThread&) = delete;

    virtual void startProcessing() = 0;
    virtual void stopProcessing() = 0;
    virtual bool isRunning() = 0;
};

}

#endif // end ATThread