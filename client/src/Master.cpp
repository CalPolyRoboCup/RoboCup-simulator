#include "Master.h"
#include "grSim_Packet.pb.h"
#include <iostream>

Master::Master()
{
    for (unsigned char i = 0; i < TEAM_SIZE; i++)
    {
        m_yellowBots[i] = new Robot(YELLOW, i);
        m_blueBots[i] = new Robot(BLUE, i);
    }

    m_pClient = new RoboCupSSLClient(10020, "224.5.23.2", "");
    m_pClient->open();
}

void Master::run()
{
    while (true)
    {
        SSL_WrapperPacket wrapperPacket;

        if (m_pClient->receive(wrapperPacket))
        {
            SSL_DetectionFrame frame = wrapperPacket.detection();

            int yellowSize = frame.robots_yellow_size();

            for (int i = 0; i < yellowSize; i++)
            {
                SSL_DetectionRobot robot = frame.robots_yellow(i);
                m_yellowBots[robot.robot_id()]->refresh(robot);
            }

            int blueSize = frame.robots_blue_size();

            for (int i = 0; i < blueSize; i++)
            {
                SSL_DetectionRobot robot = frame.robots_blue(i);
                m_blueBots[robot.robot_id()]->refresh(robot);
            }

            double updateTime = frame.t_capture();
            double deltaTime = updateTime - m_lastUpdateTime;

            if (deltaTime == 0.0)
                continue;

            m_lastUpdateTime = updateTime;

            update(deltaTime);
        }
    }
}
