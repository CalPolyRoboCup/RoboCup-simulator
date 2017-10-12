#include <iostream>
#include "ClientMaster.h"

int main()
{
    ClientMaster master = ClientMaster(10020, "224.5.23.2", YELLOW);
    master.run();
}
