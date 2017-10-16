#include "ClientMaster.h"
#include <iostream>
#include <QString>
#include <QKeyEvent>
#include <qmath.h>

ClientMaster::ClientMaster(qint16 port, const std::string netAddress, Team team, QWidget* parent) :
    Master(port, netAddress, parent),
    m_team(team)
{
    m_teamBots = m_team == YELLOW ? m_yellowBots : m_blueBots;
    m_pUdpSocket = new QUdpSocket();
}

void ClientMaster::update(double deltaTime)
{
    // Creates the packet and initializes the metadata
    grSim_Packet simPacket;
    simPacket.mutable_commands()->set_isteamyellow(m_team == YELLOW);
    simPacket.mutable_commands()->set_timestamp(0.0);

    // Update each robot on the controlling team
    for (int i = 0; i < TEAM_SIZE; i++)
    {   
        m_teamBots[i]->update(simPacket.mutable_commands()->add_robot_commands(), deltaTime);
    }

    // Serialize the packet and send it to grSim
    QByteArray dgram;
    dgram.resize(simPacket.ByteSize());
    simPacket.SerializeToArray(dgram.data(), dgram.size());
    m_pUdpSocket->writeDatagram(dgram, QHostAddress("127.0.0.1"), 20011);
}

void ClientMaster::keyPressEvent(QKeyEvent* e)
{
    float targetDirection;

    switch (e->key())
    {
    case Qt::Key_Right:
        targetDirection = 0.0f;
        break;
    case Qt::Key_Up:
        targetDirection = M_PI * 1.5f;
        break;
    case Qt::Key_Left:
        targetDirection = M_PI;
        break;
    case Qt::Key_Down:
        targetDirection = M_PI * 0.5f;
        break;
    default:
        return;
    }

    Robot* r = m_teamBots[0];

    r->setTargetDirection(targetDirection);
    r->setTargetSpeed(3.0f);
}

void ClientMaster::keyReleaseEvent(QKeyEvent* e)
{
    Robot* r = m_teamBots[0];
    r->setTargetSpeed(0.0f);
}
