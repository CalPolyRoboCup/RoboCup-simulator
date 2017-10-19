#include "TestCommandSeries.h"
#include "TestCommand.h"
#include <iostream>

TestCommandSeries::TestCommandSeries(Master* pMaster) :
    CommandSeries(pMaster)
{
    addCommand(new TestCommand(pMaster, "Command 1", 3));
    addCommand(new TestCommand(pMaster, "Command 2", 5));
}

void TestCommandSeries::start()
{
    std::cout << "Command series started!\n";

    CommandSeries::start();
}

void TestCommandSeries::end()
{
    std::cout << "Command series ended!\n";
}
