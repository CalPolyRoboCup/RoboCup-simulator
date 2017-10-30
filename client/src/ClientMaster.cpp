#include "ClientMaster.h"
#include <iostream>
#include <QString>
#include <QKeyEvent>
#include <qmath.h>
#include <cmath>
#include "commands/PassToRobot.h"
#include "commands/AimAtRobot.h"
#include "commands/GetOpen.h"

ClientMaster::ClientMaster(qint16 port, const std::string netAddress, Team team, QWidget* parent) :
    Master(port, netAddress, team, parent)
{
    m_pUdpSocket = new QUdpSocket();

    for (int i = 0; i < TEAM_SIZE; i++)
        getTeamBot(i)->setDefaultCommand(new GetOpen(this));

    getTeamBot(0)->runCommmand(new PassToRobot(this, getTeamBot(1)));
}

void ClientMaster::writeOutput()
{
    // Creates the packet and initializes the metadata
    grSim_Packet simPacket;
    simPacket.mutable_commands()->set_isteamyellow(getTeam() == YELLOW);
    simPacket.mutable_commands()->set_timestamp(0.0);

    for (int i = 0; i < TEAM_SIZE; i++)
        getTeamBot(i)->writeOutput(simPacket.mutable_commands()->add_robot_commands());

    // Serialize the packet and send it to grSim
    QByteArray dgram;
    dgram.resize(simPacket.ByteSize());
    simPacket.SerializeToArray(dgram.data(), dgram.size());
    m_pUdpSocket->writeDatagram(dgram, QHostAddress("127.0.0.1"), 20011);
}
