//************************************************************************************
// Nom du fichier : piloteI2C.c  
// Auteur : Harold Malbrouck 
//
// Date de création : 30 Mai 2025
//
// Description : Couche pilote pour la communication I²C.
//               Ce module gère l’ouverture du périphérique I2C et l’envoi de données.
//************************************************************************************
#include "../include/piloteI2C.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <syslog.h>

int piloteI2C_initialise(const char *device, int adresse) {
//******************************************************************************************
// Initialise un périphérique I2C en ouvrant le fichier et en configurant l'adresse esclave
//******************************************************************************************
    int fd = open(device, O_RDWR);  // Ouvre le périphérique en lecture/écriture
    if (fd < 0) {
        syslog(LOG_ERR, "Erreur ouverture périphérique I2C");
        return -1;
    }
    if (ioctl(fd, I2C_SLAVE, adresse) < 0) { // Définit l’adresse esclave
        syslog(LOG_ERR, "Erreur configuration adresse I2C");
        close(fd);
        return -1;
    }
    return fd;  // Retourne le descripteur de fichier valide
}

int piloteI2C_ecrire(int fd, unsigned char *data, int longueur) {
//************************************************************************************
// Envoie un tableau de données sur le bus I2C.
//************************************************************************************
    return write(fd, data, longueur);
}