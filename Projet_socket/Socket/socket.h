#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>



class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);

    void Connect ();
    void envoyerMessages(const QString &message);

private slots:
    void donneesRecues();

signals:

private:
    QTcpSocket *socket;
    quint16 tailleMessage;

};

#endif // SOCKET_H
