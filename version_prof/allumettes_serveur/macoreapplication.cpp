#include "macoreapplication.h"

MaCoreApplication::MaCoreApplication(int &argc, char **argv)
    : QCoreApplication(argc,argv)
{
    m_serveur = new Serveur();
}

MaCoreApplication::~MaCoreApplication()
{

}
