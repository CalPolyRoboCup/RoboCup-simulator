#ifndef CLIENTMASTER_H
#define CLIENTMASTER_H

#include "Master.h"
#include <QUdpSocket>

/**
 * @brief The ClientMaster class derives from @see Master and implement communication to the grSim client
 */
class ClientMaster : public Master
{
private:
    Team m_team;
    Robot** m_teamBots;

    QUdpSocket* m_pUdpSocket;

public:
    /**
     * @brief Initializes a new ClientMaster instance
     * @param port The vision mulicast port
     * @param netAddress The vision multicast address
     * @param team The team the @see ClientMaster is controlling
     */
    ClientMaster(qint16 port, const std::string netAddress, Team team);

    /**
     * @brief update Updates each child robot and sends command packets to grSim
     * @param deltaTime the time passed since the last update
     */
    virtual void update(double deltaTime);
};

#endif // CLIENTMASTER_H
