#include "Master.h"
#include <iostream>
#include <QPainter>
#include <QMatrix>
#include <QImage>
#include <qmath.h>

Master::Master(qint16 port, const std::string netAddress, QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Cal Poly RoboCup SSL Engine");
    setFixedSize(m_WIDTH, m_HEIGHT);

    // Initailize each team of robots
    for (unsigned char i = 0; i < TEAM_SIZE; i++)
    {
        m_yellowBots[i] = new Robot(YELLOW, i);
        m_blueBots[i] = new Robot(BLUE, i);
    }

    m_pFieldPixmap = new QPixmap();
    m_pYellowBot = new QPixmap();
    m_pBlueBot = new QPixmap();

    m_pFieldPixmap->load(":/images/Field.png");
    m_pYellowBot->load(":/images/YellowBot.png");
    m_pBlueBot->load(":/images/BlueBot.png");

    // Open the SSL client
    m_pClient = new RoboCupSSLClient(port, netAddress, "");
    m_pClient->open();

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(run()));
    m_pTimer->start(0);
}

void Master::run()
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
            repaint();
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

void Master::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform, true);
    painter.setPen(Qt::black);

    painter.drawPixmap(0, 0, m_WIDTH, m_HEIGHT, *m_pFieldPixmap);

    for (int i = 0; i < TEAM_SIZE; i++)
    {
        QPoint robotPoint = m_yellowBots[i]->getPosition().toPoint() * 0.1;
        robotPoint.setY(robotPoint.y() * -1);
        robotPoint += QPoint(m_WIDTH / 2, m_HEIGHT / 2);

        painter.translate(robotPoint.x(), robotPoint.y());
        painter.rotate(-m_yellowBots[i]->getOrientation() * (180.0 / M_PI));

        painter.drawPixmap(-9, -9, 18, 18, *m_pYellowBot);

        painter.resetTransform();

        robotPoint = m_blueBots[i]->getPosition().toPoint() * 0.1;
        robotPoint.setY(robotPoint.y() * -1);
        robotPoint += QPoint(m_WIDTH / 2, m_HEIGHT / 2);

        painter.translate(robotPoint.x(), robotPoint.y());
        painter.rotate(-m_blueBots[i]->getOrientation() * (180.0 / M_PI));

        painter.drawPixmap(-9, -9, 18, 18, *m_pBlueBot);

        painter.resetTransform();
    }
}
