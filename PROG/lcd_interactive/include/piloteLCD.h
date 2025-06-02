//************************************************************************************
// Nom du fichier : piloteLCD.h 
// Auteur : Harold Malbrouck 
//
// Date de création : 30 Mai 2025
// Rev : 1.0
//       2.0 01 Juin 2025 
//
// Interface du module pilote bas niveau pour le bus I2C
//************************************************************************************#ifndef PILOTE_LCD_H
#define PILOTE_LCD_H

#include <stdint.h>

void piloteLCD_init(int fd, int addr);
void piloteLCD_envoyerCommande(uint8_t cmd);
void piloteLCD_envoyerData(uint8_t data);
void piloteLCD_envoyerByte(uint8_t val, int mode);

#endif