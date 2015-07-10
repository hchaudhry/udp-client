/* CHAUDHRY Hussam
   4A AL2 */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int clientSocket, portNum, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    char *connection_msg = "Connect";
    int connected = 0;

    /* Création socket UDP */
    clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

    /* Configuration de la struct pour l'adresse */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891); // Port
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /* Initialisation de la variable de taille */
    addr_size = sizeof serverAddr;

    while(1){
        nBytes = strlen(buffer) + 1;

        if (connected == 0) {
            strncpy(buffer, connection_msg, 1024);
        }

        /* Envoi du message au serveur */
        sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

        /* Reception depuis le serveur */
        nBytes = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);


        if (connected == 0) {
            printf("Numéro client : %s\n", buffer);
        }

        if (connected == 1) {
            printf("%s\n", buffer);
        }

        connected = 1;

        if (connected == 1) {
            //printf("Tapez une commande : ");
            scanf("%s" , buffer);

            char * deconnexion_ptr = strstr(buffer,"deconnexion");
            if (deconnexion_ptr != NULL) {
                sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);
                printf("Vous êtes déconnecté\n");
                close(clientSocket);
                exit(0);
            }
        }
    }

    return 0;
}
