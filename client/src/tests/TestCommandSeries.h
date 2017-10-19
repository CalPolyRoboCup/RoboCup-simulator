#ifndef TESTCOMMANDSERIES_H
#define TESTCOMMANDSERIES_H

#include "../CommandSeries.h"

class TestCommandSeries : public CommandSeries
{
public:
    TestCommandSeries(Master* pMaster);

    virtual void start();

    virtual void end();
};

#endif // TESTCOMMANDSERIES_H
