#include "Master.h"
#include "grSim_Packet.pb.h"
#include <iostream>

Master::Master(qint16 port, const std::string netAddress)
{
    // Initailize each team of robots
    for (unsigned char i = 0; i < TEAM_SIZE; i++)
    {
        m_yellowBots[i] = new Robot(YELLOW, i);
        m_blueBots[i] = new Robot(BLUE, i);
    }

    // Open the SSL client
    m_pClient = new RoboCupSSLClient(port, netAddress, "");
    m_pClient->open();
}

void Master::run()
{
    while (true)
    {
        SSL_WrapperPacket wrapperPacket;

        // If a packet was received, update robot information
        if (m_pClient->receive(wrapperPacket))
        {
            SSL_DetectionFrame frame = wrapperPacket.detection();

            // Calculate the delta time and update the robots if this is the start of a new frame
            double updateTime = frame.t_capture();
            double deltaTime = updateTime - m_lastUpdateTime;

            if (deltaTime > 0.0)
            {
                m_lastUpdateTime = updateTime;
                update(deltaTime);
            }

            // Update each yellow robot
            int yellowSize = frame.robots_yellow_size();

            for (int i = 0; i < yellowSize; i++)
            {
                SSL_DetectionRobot robot = frame.robots_yellow(i);
                m_yellowBots[robot.robot_id()]->refresh(robot);
            }

            // Update each blue robot
            int blueSize = frame.robots_blue_size();

            for (int i = 0; i < blueSize; i++)
            {
                SSL_DetectionRobot robot = frame.robots_blue(i);
                m_blueBots[robot.robot_id()]->refresh(robot);
            }
        }
    }
}
