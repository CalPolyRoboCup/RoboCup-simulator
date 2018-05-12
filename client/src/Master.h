#ifndef MASTER_H
#define MASTER_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include "Team.h"
#include "RobotManager.h"
#include "Robot.h"
#include "Ball.h"
#include "robocup_ssl_client.h"

#define FIXED_DELTA_TIME 1.0f/60.0f

class Robot;
class RobotManager;

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
     * @brief Frees any dynamically allocated memory by the Master class
     */
    virtual ~Master();

    /**
     * @brief Returns the yellow bot of the given ID
     * @param id The ID of the yellow robot to access
     * @return The yellow robot of the given ID
     */
    Robot* getYellowBot(int id);

    /**
     * @brief Returns the blue bot of the given ID
     * @param id The ID of the blue robot to access
     * @return The blue robot of the given ID
     */
    Robot* getBlueBot(int id);

    /**
     * @brief Returns the bot on the controlling team of the given ID
     * @param id The ID of the robot to access
     * @return The robot of the given ID
     */
    Robot* getTeamBot(int id);

    /**
     * @brief Returns the bot on the opposing team of the given ID
     * @param id The ID of the robot to access
     * @return The robot of the given ID
     */
    Robot* getOpponentBot(int id);

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

    /**
     * @brief Returns the number of yellow bots in the game
     * @return The number of yellow bots in the game
     */
    int getNumYellowBots() const;

    /**
     * @brief Returns the number of blue bots in the game
     * @return The number of blue bots in the game
     */
    int getNumBlueBots() const;

    /**
     * @brief Returns the number of team bots in the game
     * @return The number of team bots in the game
     */
    int getNumTeamBots() const;

    /**
     * @brief Returns the number of opponent bots in the game
     * @return The number of opponent bots in the game
     */
    int getNumOpponentBots() const;

    /**
     * @brief Converts world coordinates to a point on the screen
     * @param point The point to convert
     * @return The converted point
     */
    QPoint convertToScreenPoint(QVector2D point);

protected:

    /**
     * @brief Defines how communication is completed with the robots
     * @param deltaTime the time passed since the last writeOutput call
     */
    virtual void writeOutput() = 0;

private:
    const int m_WIDTH;
    const int m_HEIGHT;

    int m_framesUntilStart;

    RobotManager* m_yellowBots;
    RobotManager* m_blueBots;

    Ball* m_ball;

    Team m_team;
    RobotManager* m_teamBots;
    RobotManager* m_opponentBots;

    QPixmap* m_pFieldPixmap;
    QPixmap* m_pYellowBot;
    QPixmap* m_pBlueBot;

    RoboCupSSLClient* m_pClient;
    QTimer* m_pTimer;
    int m_lastFrameNumber;

    void update(double deltaTime);

    void paintEvent(QPaintEvent* e);

public slots:

    /**
     * @brief run Receives any packets sent from SSL_Vision, refreshes the robots' positions,
     * updates the robots, then redraws the window
     */
    void run();
};

#endif // MASTER_H
