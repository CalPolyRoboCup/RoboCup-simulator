#ifndef MASTER_H
#define MASTER_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include "Robot.h"
#include "robocup_ssl_client.h"

#define TEAM_SIZE 6

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
    explicit Master(qint16 port, const std::string netAddress, QWidget* parent = 0);

protected:
    Robot* m_yellowBots[TEAM_SIZE];
    Robot* m_blueBots[TEAM_SIZE];

private:
    const int m_WIDTH = 1040;
    const int m_HEIGHT = 740;

    QPixmap* m_pFieldPixmap;
    QPixmap* m_pYellowBot;
    QPixmap* m_pBlueBot;

    RoboCupSSLClient* m_pClient;
    QTimer* m_pTimer;
    double m_lastUpdateTime;

    void paintEvent(QPaintEvent* e);

    virtual void update(double deltaTime) = 0;

public slots:

    /**
     * @brief run Receives any packets sent from SSL_Vision, refreshes the robots' positions,
     * updates the robots, then redraws the window
     */
    void run();
};

#endif // MASTER_H
