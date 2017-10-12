#ifndef MASTER_H
#define MASTER_H

#include "Robot.h"
#include "robocup_ssl_client.h"

#define TEAM_SIZE 6

class Master
{
private:
    RoboCupSSLClient* m_pClient;
    double m_lastUpdateTime;

    virtual void update(double deltaTime) = 0;

protected:
    Robot* m_yellowBots[TEAM_SIZE];
    Robot* m_blueBots[TEAM_SIZE];

public:
    Master();

    void run();
};

#endif // MASTER_H
