#include "ClientMainWindow.h"                                                                                // Inclusion du fichier d'en-tête de la classe ClientMainWindow
#include "ui_ClientMainWindow.h"                                                                            // Inclusion du fichier d'en-tête généré par Qt pour l'interface utilisateur

ClientMainWindow::ClientMainWindow(QWidget *parent)
    : QMainWindow(parent),                                                                                 // Initialisation du constructeur de la classe de base (QMainWindow)
    ui(new Ui::ClientMainWindow),                                                                          // Initialisation de l'interface utilisateur
    tcpSocket(new QTcpSocket(this))                                                                        // Initialisation du socket TCP
{
    ui->setupUi(this);                                                                                     // Configuration de l'interface utilisateur à partir du fichier UI généré par Qt

    connect(ui->sendButton, &QPushButton::clicked, this, &ClientMainWindow::on_sendButton_clicked);
                                                                                                           // Connexion du clic sur le bouton "sendButton" au slot "on_sendButton_clicked" de cette classe
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientMainWindow::readData);
                                                                                                           // Connexion du signal "readyRead" du socket TCP au slot "readData" de cette classe

                                                                                                           // Connexion au serveur en utilisant l'adresse IP 127.0.0.1 et le port 8000
    tcpSocket->connectToHost("127.0.0.1", 8000);
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;                                                                                              // Libération de la mémoire allouée pour l'interface utilisateur
}

void ClientMainWindow::on_sendButton_clicked()
{
    // Send the "Hello" request to the server
    QByteArray message = "Hello ";                                                                           // Création d'un tableau de bytes contenant le message "Hello"
    tcpSocket->write(message);                                                                               // Envoi du message au serveur via le socket TCP
}

void ClientMainWindow::readData()
{
                                                                                                             // Read and display data received from the server
    QString data = QString::fromUtf8(tcpSocket->readAll());                                                  // Lecture des données du socket et conversion en QString
    qDebug() << "Données envoyez par le serveur :" << data;                                                  // Affichage des données dans la console de débogage
    ui->textBrowser->append("Données envoyées par le serveur : " + data);
                                                                                                             // Ajout des données à la zone de texte "textBrowser" de l'interface utilisateur
}
