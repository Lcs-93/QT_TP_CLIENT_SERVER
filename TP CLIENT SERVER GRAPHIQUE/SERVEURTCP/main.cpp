#include <QCoreApplication>;                                                                                            // Inclusion de la bibliothèque principale de Qt pour les applications en ligne de commande
#include <QDebug>;                                                                                                      // Inclusion de la bibliothèque de débogage de Qt
#include <QtNetwork>;                                                                                                   // Inclusion de la bibliothèque réseau de Qt

class Server : public QObject                                                                                           // Définition de la classe Server héritant de QObject
{
    Q_OBJECT                                                                                                            // Macro Qt permettant d'utiliser les fonctionnalités liées aux signaux et slots
public:
    Server(QObject *parent = nullptr) : QObject(parent)                                                                 // Constructeur de la classe Server avec initialisation du parent
    {
        tcpServer = new QTcpServer(this);                                                                               // Création d'un objet QTcpServer
        connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
                                                                                                                        // Connexion du signal newConnection du serveur à la fonction newConnection de cette classe

                                                                                                                        // Modification : Utilisation de QHostAddress::Any pour écouter sur toutes les interfaces
        if (!tcpServer->listen(QHostAddress::Any, 8000))                                                                // Tentative de démarrage du serveur sur le port 8000
        {
            qDebug() << "Le serveur n'a pas pu démarrer. Erreur :" << tcpServer->errorString();
                                                                                                                        // Affichage d'un message d'erreur en cas d'échec de démarrage
        }
        else
        {
            qDebug() << "Le serveur a démarré.";                                                                        // Affichage d'un message de succès en cas de démarrage réussi
        }
    }

private slots:
    void newConnection()                                                                                                 // Slot appelé lorsqu'une nouvelle connexion est établie
    {
        QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
                                                                                                                         // Obtention d'un pointeur vers le socket du client qui vient de se connecter
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readData);
                                                                                                                        // Connexion du signal readyRead du socket client à la fonction readData de cette classe
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
                                                                                                                        // Connexion du signal disconnected du socket client à la suppression asynchrone du socket

        qDebug() << "Client connecté.";                                                                                 // Affichage d'un message indiquant la connexion du client
    }

    void readData()                                                                                                     // Slot appelé lorsqu'il y a des données à lire depuis un client
    {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
                                                                                                                        // Obtention d'un pointeur vers le socket du client émettant le signal
        if (!clientSocket)
            return;                                                                                                     // Retour si le cast du pointeur échoue

        QString data = QString::fromUtf8(clientSocket->readAll());
                                                                                                                        // Lecture des données du socket client et conversion en QString
        qDebug() << "Données reçues du client :" << data;                                                               // Affichage des données reçues du client

        // Envoyer une réponse au client
        clientSocket->write("Bonjour CLIENT");                                                                          // Envoi d'une réponse au client

        // Ajouter un message de débogage
        qDebug() << "Réponse envoyée au client.";                                                                       // Affichage d'un message indiquant l'envoi de la réponse
    }

private:
    QTcpServer *tcpServer;                                                                                              // Pointeur vers l'objet QTcpServer
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);                                                                                     // Création d'une application Qt
    Server server;                                                                                                      // Création de l'objet Server
    return a.exec();                                                                                                    // Exécution de l'application Qt
}

#include "main.moc"                                                                                                     // Inclusion du fichier moc généré par Qt (Meta-Object Compiler)
