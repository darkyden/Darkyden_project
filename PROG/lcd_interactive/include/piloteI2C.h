//************************************************************************************
// Nom du fichier : piloteI2C.h 
// Auteur : Harold Malbrouck 
//
// Date de création : 30 Mai 2025
// Rev : 1.0
//       2.0 01 Juin 2025 
//
// Interface du module pilote bas niveau pour le bus I2C
//************************************************************************************
#ifndef PILOTE_I2C_H
#define PILOTE_I2C_H

// Initialise un périphérique I2C à l'adresse spécifiée
int piloteI2C_initialise(const char *device, int adresse);

// Envoie un octet sur le bus I2C ouvert
int piloteI2C_ecrire(int fd, unsigned char *data, int longueur);

#endif