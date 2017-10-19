#ifndef MASTER_H
#define MASTER_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include "Robot.h"
#include "Ball.h"
#include "Team.h"
#include "robocup_ssl_client.h"

#define TEAM_SIZE 6

class Robot;

/**
 * @brief The Master class is an abstract class that handles receiving packets from the SSL server and updating robot information
 */
class Master : public QWidget
{
    Q_OBJECT
public:
     /**
     * @brief Initializes a new instance of the Master class
     * @param port The vision mulicast port
     * @param netAddress The vision multicast address
     * @param parent The parent QWidget to the Master instance
     */
    explicit Master(qint16 port, const std::string netAddress, Team team, QWidget* parent = 0);

    /**
     * @brief Returns the yellow bot of the given ID
     * @param id The ID of the yellow robot to access
     * @return The yellow robot of the given ID
     */
    Robot* getYellowBot(int id) const { return m_yellowBots[id]; }

    /**
     * @brief Returns the blue bot of the given ID
     * @param id The ID of the blue robot to access
     * @return The blue robot of the given ID
     */
    Robot* getBlueBot(int id) const { return m_blueBots[id]; }

    /**
     * @brief Returns the bot on the controlling team of the given ID
     * @param id The ID of the robot to access
     * @return The robot of the given ID
     */
    Robot* getTeamBot(int id) const { return m_teamBots[id]; }

    /**
     * @brief Returns the bot on the opposing team of the given ID
     * @param id The ID of the robot to access
     * @return The robot of the given ID
     */
    Robot* getOpponentBot(int id) const { return m_opponentBots[id]; }

    /**
     * @brief Returns the Ball instance
     * @return The Ball instance
     */
    Ball* getBall() const { return m_ball; }

    /**
     * @brief Returns the @see Team that Master is controlling
     * @return The Team that master is controlling
     */
    Team getTeam() const { return m_team; }

protected:

    /**
     * @brief Defines how communication is completed with the robots
     * @param deltaTime the time passed since the last writeOutput call
     */
    virtual void writeOutput() = 0;

private:
    const int m_WIDTH;
    const int m_HEIGHT;

    Robot* m_yellowBots[TEAM_SIZE];
    Robot* m_blueBots[TEAM_SIZE];

    Ball* m_ball;

    Team m_team;
    Robot** m_teamBots;
    Robot** m_opponentBots;

    QPixmap* m_pFieldPixmap;
    QPixmap* m_pYellowBot;
    QPixmap* m_pBlueBot;

    RoboCupSSLClient* m_pClient;
    QTimer* m_pTimer;
    double m_lastUpdateTime;

    void update(double deltaTime);

    void paintEvent(QPaintEvent* e);

    QPoint convertToScreenPoint(QVector2D point);

public slots:

    /**
     * @brief run Receives any packets sent from SSL_Vision, refreshes the robots' positions,
     * updates the robots, then redraws the window
     */
    void run();
};

#endif // MASTER_H
