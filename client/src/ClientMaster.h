#ifndef CLIENTMASTER_H
#define CLIENTMASTER_H

#include "Master.h"
#include <QUdpSocket>

class ClientMaster : public Master
{
private:
    Team m_team;
    Robot** m_teamBots;

    QUdpSocket* m_pUdpSocket;

public:
    ClientMaster(Team team);

    virtual void update(double deltaTime);
};

#endif // CLIENTMASTER_H
