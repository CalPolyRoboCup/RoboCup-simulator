#ifndef MASTER_H
#define MASTER_H

#include "Robot.h"
#include "robocup_ssl_client.h"

#define TEAM_SIZE 6

/**
 * @brief The Master class is an abstract class that handles receiving packets from the SSL server and updating robot information
 */
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
    /**
     * @brief Initializes a new instance of the Master class
     * @param port The vision mulicast port
     * @param netAddress The vision multicast address
     */
    Master(qint16 port, const std::string netAddress);

    void run();
};

#endif // MASTER_H
