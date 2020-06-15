#include <QCoreApplication>
#include "socket.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Socket cSocket;
    cSocket.Connect();
    cSocket.envoyerMessages("Bonjour");

    return a.exec();
}
