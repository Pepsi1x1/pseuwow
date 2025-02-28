#ifndef _CLI_H
#define _CLI_H

class PseuInstance;

class CliRunnable : public ZThread::Runnable
{
public:
    CliRunnable(PseuInstance*);
    void run(void);
    void stop(void);

private:
    bool _stop;
    PseuInstance *_instance;
};

#endif
