#include "ClientMaster.h"
#include <iostream>
#include <QString>
#include <QKeyEvent>
#include <qmath.h>
#include <cmath>

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
    updateDirections(e->key(), true);
}

void ClientMaster::keyReleaseEvent(QKeyEvent* e)
{
    updateDirections(e->key(), false);
}

void ClientMaster::updateDirections(int key, bool pressed)
{
    if (pressed)
    {
        if (getKeyIndex(key) == -1)
            return;
        else
            m_directions.push_back(key);
    }
    else
    {
        if (std::find(m_directions.begin(), m_directions.end(), key) != m_directions.end())
            m_directions.erase(std::remove(m_directions.begin(), m_directions.end(), key), m_directions.end());
        else
            return;
    }

    Robot* r = m_teamBots[0];

    if (m_directions.empty())
    {
        r->setTargetSpeed(0.0f);
    }
    else
    {
        float targetDirection = getKeyIndex(m_directions.back()) * M_PI * 0.5;

        r->setTargetDirection(targetDirection);
        r->setTargetSpeed(3.0f);
    }
}

int ClientMaster::getKeyIndex(int key)
{
    switch (key)
    {
    case Qt::Key_Right:
        return 0;
    case Qt::Key_Down:
        return 1;
    case Qt::Key_Left:
        return 2;
    case Qt::Key_Up:
        return 3;
    default:
        return -1;
    }
}
