#ifndef CLIENTMAINWINDOW_H                         // Directive de préprocesseur pour éviter l'inclusion multiple du fichier d'en-tête
#define CLIENTMAINWINDOW_H

#include <QMainWindow>                             // Inclusion du fichier d'en-tête de la classe QMainWindow
#include <QTcpSocket>                              // Inclusion du fichier d'en-tête de la classe QTcpSocket
#include <QHostAddress>                            // Inclusion du fichier d'en-tête pour QHostAddress

QT_BEGIN_NAMESPACE                                 // Début du namespace Qt
namespace Ui {
class ClientMainWindow;
}
QT_END_NAMESPACE                                   // Fin du namespace Qt

class QTcpSocket;                                   // Déclaration avant de l'utiliser dans la classe

class ClientMainWindow : public QMainWindow        // Définition de la classe ClientMainWindow héritant de QMainWindow
{
    Q_OBJECT                                       // Macro Qt permettant d'utiliser les fonctionnalités liées aux signaux et slots

public:
    ClientMainWindow(QWidget *parent = nullptr);   // Constructeur de la classe avec un paramètre optionnel parent
    ~ClientMainWindow();                            // Destructeur de la classe

private slots:
    void on_sendButton_clicked();                  // Slot appelé lorsqu'un bouton est cliqué
    void readData();                               // Slot appelé lorsqu'il y a des données à lire

private:
    Ui::ClientMainWindow *ui;                      // Pointeur vers l'interface utilisateur générée par Qt
    QTcpSocket *tcpSocket;                         // Pointeur vers l'objet QTcpSocket pour la communication réseau
};

#endif // CLIENTMAINWINDOW_H                       // Fin de la directive de préprocesseur
