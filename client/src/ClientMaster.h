#ifndef CLIENTMASTER_H
#define CLIENTMASTER_H

#include "Master.h"
#include <QUdpSocket>
#include <vector>

/**
 * @brief The ClientMaster class derives from @see Master and implement communication to the grSim client
 */
class ClientMaster : public Master
{
public:
    /**
     * @brief Initializes a new ClientMaster instance
     * @param port The vision mulicast port
     * @param netAddress The vision multicast address
     * @param team The team the @see ClientMaster is controlling
     */
    ClientMaster(qint16 port, const std::string netAddress, Team team, QWidget* parent = 0);

    /**
     * @brief Destroys any dynamically allocated memory by the ClientMaster
     */
    ~ClientMaster();

protected:

    /**
     * @brief update Updates each child robot and sends command packets to grSim
     * @param deltaTime the time passed since the last update
     */
    virtual void writeOutput();

private:
    QUdpSocket* m_pUdpSocket;

};


#endif // CLIENTMASTER_H
