# QT_TP_CLIENT_SERVER

 ## Prérequis - il faut installer QT 
- video QT CREATOR : https://www.youtube.com/watch?v=JDIV3DZTWSY
  
## Importer	le projet Qt	nommé « client_TCP_eleve »,	ajouter	dans	le	fichier	.pro les fichier sont dans ce repository https://github.com/alitobji/TP_QT_Socket_eleve
ajouter ces lignes de code suivant dans le fichier client.cpp dans le constructeur CLIENT
    QObject::connect(tcpSocket, SIGNAL(connected()), this,  SLOT (estConnectee()) );
    QObject::connect(tcpSocket, SIGNAL(disconnected()), this,  SLOT(estDeconnectee()) );
    QObject::connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError) ), this, SLOT (gestionErreur(QAbstractSocket::SocketError)) );
    QObject::connect(tcpSocket, SIGNAL(readyRead()),this, SLOT(recevoir()) );
    
pensez a changer ces lignes afin de vous connectez au server 
  tcpSocket->connectToHost(QHostAddress("127.0.0.1"), PORT_SERVEUR);
  tcpSocket->connectToHost(QHostAddress::LocalHost, PORT_SERVEUR);
  
rajouter cette ligne afin d'afficher les données 

QByteArray donne = tcpSocket->readAll();
    qDebug() << "Des donnes ont ete reçues : ";
   // afficher les données reçues dans un qdebug ici....
    qDebug() <<donne;


 #### LANCER VOTRE SERVEUR NETCAT  :
 - Ouvrez un terminal executez la commande suivante afin de créer le serveur 
   while true; do (echo "Hello" | nc -l -p 8000) done


### LANCER LE CLIENT

vous pouvez executez votre projet client qui va envoyez une donnees au serveur et renvoyez une donnée au client.

## PARTIE 2
-télécharger le fichier zip TP CLIENT SERVER TERMINAL 
-éxecuter les deux projet client et server 
-cela devrait afficher dans le terminal les données recu et envoyez 

## PARTIE 3
-télécharger le fichier zip TP CLIENT SERVER GRAPHIQUE 
-executer les deux projet 
-appuyez sur le bouton de l'interface graphique pour envoyez des données et en recevoir par le serveur 
