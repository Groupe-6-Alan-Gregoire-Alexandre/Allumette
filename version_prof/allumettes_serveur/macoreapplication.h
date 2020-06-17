#ifndef MACOREAPPLICATION_H
#define MACOREAPPLICATION_H

#include <QCoreApplication>
#include "serveur.h"

class MaCoreApplication : public QCoreApplication
{
    public:
        MaCoreApplication(int &argc, char **argv);
        ~MaCoreApplication();

    private:
        Serveur * m_serveur;
};

#endif // MACOREAPPLICATION_H
