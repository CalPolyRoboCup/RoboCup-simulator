#include "ClientMaster.h"
#include <iostream>
#include <QString>
#include <qmath.h>

ClientMaster::ClientMaster(Team team) :
    m_team(team)
{
    m_teamBots = m_team == YELLOW ? m_yellowBots : m_blueBots;
    m_pUdpSocket = new QUdpSocket();
}

void ClientMaster::update(double deltaTime)
{
    grSim_Packet simPacket;
    simPacket.mutable_commands()->set_isteamyellow(m_team == YELLOW);
    simPacket.mutable_commands()->set_timestamp(0.0);

    for (int i = 0; i < TEAM_SIZE; i++)
    {
        // Testing vvv
        if (m_teamBots[i]->getId() == 0)
        {
            m_teamBots[i]->setTargetDirection(M_PI);
            m_teamBots[i]->setTargetAngularVelocity(1.0f);
            m_teamBots[i]->setTargetSpeed(1.0f);
        }
        // Testing ^^^

        m_teamBots[i]->update(simPacket.mutable_commands()->add_robot_commands(), deltaTime);
    }

    QByteArray dgram;
    dgram.resize(simPacket.ByteSize());
    simPacket.SerializeToArray(dgram.data(), dgram.size());
    m_pUdpSocket->writeDatagram(dgram, QHostAddress("127.0.0.1"), 20011);
}
