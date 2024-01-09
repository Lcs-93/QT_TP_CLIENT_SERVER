#include <QCoreApplication>
#include <QDebug>
#include <QCoreApplication>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QtNetwork>
class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr) : QObject(parent)
    {
        tcpServer = new QTcpServer(this);
        connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);

        // Modification : Utilisation de QHostAddress::Any pour écouter sur toutes les interfaces
        if (!tcpServer->listen(QHostAddress::Any, 8000))
        {
            qDebug() << "Le serveur n'a pas pu démarrer. Erreur :" << tcpServer->errorString();
        }
        else
        {
            qDebug() << "Le serveur a démarré.";
        }
    }

private slots:
    void newConnection()
    {
        QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readData);
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
        qDebug() << "Client connecté.";
    }

    void readData()
    {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
        if (!clientSocket)
            return;

        while (clientSocket->bytesAvailable() > 0)
        {
            QString data = QString::fromUtf8(clientSocket->readAll());
            qDebug() << "Données reçues du client :" << data;

            // Envoyer une réponse au client
            clientSocket->write("World");

            // Ajouter un message de débogage
            qDebug() << "Réponse envoyée au client.";
        }
    }

private:
    QTcpServer *tcpServer;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    return a.exec();
}

#include "main.moc"
