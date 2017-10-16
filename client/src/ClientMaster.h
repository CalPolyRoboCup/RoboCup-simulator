#ifndef CLIENTMASTER_H
#define CLIENTMASTER_H

#include "Master.h"
#include <QUdpSocket>

/**
 * @brief The ClientMaster class derives from @see Master and implement communication to the grSim client
 */
class ClientMaster : public Master
{
private:
    Team m_team;
    Robot** m_teamBots;

    QUdpSocket* m_pUdpSocket;

public:
    /**
     * @brief Initializes a new ClientMaster instance
     * @param port The vision mulicast port
     * @param netAddress The vision multicast address
     * @param team The team the @see ClientMaster is controlling
     */
    ClientMaster(qint16 port, const std::string netAddress, Team team, QWidget* parent = 0);

    /**
     * @brief update Updates each child robot and sends command packets to grSim
     * @param deltaTime the time passed since the last update
     */
    virtual void update(double deltaTime);

    /**
     * @brief keyPressEvent For testing - moves the yellow robot of index 0 according to which arrow key is pressed
     * @param e The @see QKeyEvent used to determine which key is pressed
     */
    void keyPressEvent(QKeyEvent* e);

    /**
     * @brief keyReleaseEvent For testing - stops movement of the yellow robot of index 0
     * @param e The @see QKeyEvent indicating which key was released
     */
    void keyReleaseEvent(QKeyEvent* e);
};


#endif // CLIENTMASTER_H
