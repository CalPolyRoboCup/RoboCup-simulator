#include "Master.h"
#include <iostream>
#include <QPainter>
#include <QMatrix>
#include <QImage>
#include <qmath.h>

Master::Master(qint16 port, const std::string netAddress, Team team, QWidget* parent) :
    QWidget(parent),
    m_WIDTH(1040),
    m_HEIGHT(740),
    m_team(team),
    m_lastFrameNumber(0),
    m_framesUntilStart(2)
{
    setWindowTitle("Cal Poly RoboCup SSL Engine");
    setFixedSize(m_WIDTH, m_HEIGHT);

    // Initailize each team of robots
    for (unsigned char i = 0; i < TEAM_SIZE; i++)
    {
        m_yellowBots[i] = new Robot(YELLOW, i);
        m_blueBots[i] = new Robot(BLUE, i);
    }

    if (m_team == YELLOW)
    {
        m_teamBots = m_yellowBots;
        m_opponentBots = m_blueBots;
    }
    else
    {
        m_teamBots= m_blueBots;
        m_opponentBots = m_yellowBots;
    }

    m_ball = new Ball;

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

Master::~Master()
{
    delete m_ball;

    for (int i = 0; i < TEAM_SIZE; i++)
    {
        delete m_yellowBots[i];
        delete m_blueBots[i];
    }

    delete m_pClient;
    delete m_pFieldPixmap;
    delete m_pYellowBot;
    delete m_pBlueBot;
    delete m_pTimer;
}

void Master::run()
{
    SSL_WrapperPacket wrapperPacket;

    // If a packet was received, update robot information
    if (m_pClient->receive(wrapperPacket))
    {
        SSL_DetectionFrame frame = wrapperPacket.detection();

        // Calculate the delta time and update the robots if this is the start of a new frame
        int frameNumber = frame.frame_number();
        int deltaFrames = frameNumber - m_lastFrameNumber;

        if (deltaFrames > 0)
        {
            m_lastFrameNumber = frameNumber;

            if (m_framesUntilStart > 0)
                m_framesUntilStart--;
            else
                update(deltaFrames * FIXED_DELTA_TIME);
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

        if (frame.balls_size() > 0)
        {
            SSL_DetectionBall ball = frame.balls(0);
            m_ball->refresh(ball);
        }
    }
}

void Master::update(double deltaTime)
{
    // Update each robot on the controlling team
    for (int i = 0; i < TEAM_SIZE; i++)
        m_teamBots[i]->updateStats(deltaTime);

    m_ball->updateStats(deltaTime);

    for (int i = 0; i < TEAM_SIZE; i++)
        m_teamBots[i]->updateCommand(deltaTime);

    writeOutput();
    repaint();
}

void Master::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform, true);

    painter.drawPixmap(0, 0, m_WIDTH, m_HEIGHT, *m_pFieldPixmap);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);

    QPoint ballPosition = convertToScreenPoint(m_ball->getPosition());
    painter.drawEllipse(ballPosition, 2, 2);

    for (int i = 0; i < TEAM_SIZE; i++)
    {
        QPoint robotPoint = convertToScreenPoint(m_yellowBots[i]->getPosition());

        painter.translate(robotPoint.x(), robotPoint.y());
        painter.rotate(-m_yellowBots[i]->getOrientation() * (180.0 / M_PI));

        painter.drawPixmap(-9, -9, 18, 18, *m_pYellowBot);

        painter.resetTransform();

        robotPoint = convertToScreenPoint(m_blueBots[i]->getPosition());

        painter.translate(robotPoint.x(), robotPoint.y());
        painter.rotate(-m_blueBots[i]->getOrientation() * (180.0 / M_PI));

        painter.drawPixmap(-9, -9, 18, 18, *m_pBlueBot);

        painter.resetTransform();
    }

    for (int i = 0; i < TEAM_SIZE; i++)
    {
        QPoint robotPoint = convertToScreenPoint(m_yellowBots[i]->getPosition());
        painter.drawText(robotPoint.x() + 9, robotPoint.y() - 9, QString::number(i));

        robotPoint = convertToScreenPoint(m_blueBots[i]->getPosition());
        painter.drawText(robotPoint.x() + 9, robotPoint.y() - 9, QString::number(i));
    }
}

QPoint Master::convertToScreenPoint(QVector2D pos)
{
    QPoint point = pos.toPoint() * 0.1;
    point.setY(point.y() * -1);
    point += QPoint(m_WIDTH / 2, m_HEIGHT / 2);

    return point;
}
